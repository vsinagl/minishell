/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/10/31 17:17:31 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
* @brief Creates an AST node for a command.
*
* This function creates an AST node for a command based on the given token.
* The created node will have the type COMMAND and will store the command's data.
* The left and right child nodes will be set to NULL.
Command is leaf node and dont have any childs.
* It's a last instance in tree
* The function also creates arguments for the command by calling
the	create_args(void) function in tokenqueue.
 *
 * @param queue The token queue containing the tokens.
 * @param parent The parent node of the command node.
 * @param token The token representing the command.
 * @return The created AST node for the command,
	or NULL if memory allocation fails.
 */
t_astnode	*ast_command(t_tokenqueue *queue, t_astnode *parent, t_token *token)
{
	t_astnode	*node;

	node = (t_astnode *)malloc(sizeof(t_astnode));
	if (node == NULL)
		return (NULL);
	node->parent = parent;
	node->type = COMMAND;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->data = (void *)strdup(token->u_value.word);
	if (queue->size > 0 && queue->top->type == TOKEN_WORD)
		node->args = create_args(queue);
	free_token(token);
	return (node);
}

/**
 * @brief Creates a binary operation type AST node.

This function creates a binary operation AST node with
the given token as its parametrs. The binary operators are:
OP_PIPE, OP_OR, OP_AND. For now, only OP_PIPE is implemented.

the parent of this node will become the left child of the new binary (pipe node).
 the right child will become command node. After pipe, command must follow.

 example: ls | wc -l is command we want to executer.
 from parser we will have following tokesn: ls, |, wc, -l
 before creating AST node of pipe, the current as will look like this:

			ROOT
			/
			ls         <--- pipe token

 AFTER CREATING AST PIPE NODE:
			ROOT
			/
		pipe
		/	\
		ls	wc

! notice that ls become a ls was pass as parrent to ast_binaryop function
(parent of pipe token) but after this function
it become the child of pipe node.
 @inputs:
 @param queue The token queue containing the tokens to be processed.

 @param parent The parent of pipe token.
 It will actully become the left child of pipe node.
 @param token The token containing the binary operation data.
 @return The newly created binary operation AST node,
or NULL if memory allocation fails.
 */
t_astnode	*ast_binaryop(t_tokenqueue *queue, t_astnode *parent,
		t_token *token)
{
	t_astnode	*node;

	node = (t_astnode *)malloc(sizeof(t_astnode));
	if (node == NULL)
		return (NULL);
	node->type = BINARY;
	node->args = NULL;
	node->left = parent;
	node->parent = parent->parent;
	parent->parent->left = node;
	parent->parent = node;
	node->data = (void *)token->u_value.op;
	node->right = NULL;
	if (queue->size > 0 && queue->top->type == TOKEN_WORD)
		node->right = ast_command(queue, node, pop_token(queue));
	free_token(token);
	return (node);
}

enum e_nodetype	get_redirection_nodetype(enum e_operatortype op)
{
	enum e_nodetype	type;

	type = 0;
	if (op == OP_REDIRECT_OUT)
		type = REDIRECTION_OUT;
	else if (op == OP_REDIRECT_APPEND)
		type = REDIRECTION_APPEND;
	else if (op == OP_REDIRECT_IN)
		type = REDIRECTION_IN;
	else if (op == OP_HEREDOC)
		type = REDIRECTION_HEREDOC;
	return (type);
}

/**
* @brief Creates an redirection AST node.
*
* This function creates an AST node of type REDIRECTION
and initializes its properties.
* The node represents a bash redirection operator.
*
 * @param queue The token queue containing the remaining tokens.
 * @param parent The parent AST node.
 * @param token The token representing the redirection operator.
 * @return The created AST node, or NULL if memory allocation fails.
 */
t_astnode	*ast_redirection(t_tokenqueue *queue, t_astnode *parent,
		t_token *token)
{
	t_astnode	*node;

	node = (t_astnode *)malloc(sizeof(t_astnode));
	if (node == NULL)
		return (NULL);
	node->type = get_redirection_nodetype(token->u_value.op);
	node->right = NULL;
	node->args = NULL;
	node->left = parent;
	node->parent = parent->parent;
	parent->parent->left = node;
	parent->parent = node;
	node->data = NULL;
	if (queue->size > 0 && queue->top->type == TOKEN_WORD)
		node->data = (void *)strdup(pop_token(queue)->u_value.word);
	free_token(token);
	return (node);
}

/**
 * @brief Creates an Abstract Syntax Tree (AST) from a t_TokenQueue.
 *

* This function takes a t_TokenQueue(parsed tokens generated
from lexical analysis
-> lexer.c and parsed by parser.c)
 *  as input and constructs tree structure from it.
 * AST is represented byt tree with root node (special type of tree-node)
 * that represents the beggining most upper node of this tree.
 *

* @param queue The TokenQueue containing the tokens representing
commands and operators.
* @return A pointer to the root node of the constructed AST.
*/
t_astnode	*create_ast(t_tokenqueue *queue, t_shelldata *data)
{
	t_astnode	*root;
	t_astnode	*node;
	t_token		*token;

	root = ast_root(data);
	node = ast_command(queue, root, pop_token(queue));
	root->left = node;
	while (queue->size > 0)
	{
		token = pop_token(queue);
		if (token->type == TOKEN_OPERATOR)
		{
			if (token->u_value.op == OP_PIPE || token->u_value.op == OP_OR
				|| token->u_value.op == OP_AND)
				node = ast_binaryop(queue, node, token);
			else
				node = ast_redirection(queue, node, token);
		}
		else if (token->type == TOKEN_WORD)
			node = ast_command(queue, node, token);
	}
	free_token_queue(queue);
	return (root);
}
