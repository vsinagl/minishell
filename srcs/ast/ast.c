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

#include "../../includes/ast.h"

/**
* @brief Creates an AST node for a command.
* 
* This function creates an AST node for a command based on the given token.
* The created node will have the type COMMAND and will store the command's data.
* The left and right child nodes will be set to NULL.
Command is leaf node and dont have any childs.
* It's a last instance in tree
* The function also creates arguments for the command by calling 
the create_args() function in tokenqueue.
 *
 * @param queue The token queue containing the tokens.
 * @param parent The parent node of the command node.
 * @param token The token representing the command.
 * @return The created AST node for the command,
	or NULL if memory allocation fails.
 */
struct ASTNode	*ast_command(struct TokenQueue *queue, struct ASTNode *parent,
		struct Token *token)
{
	struct ASTNode	*node;

	node = (struct ASTNode *)malloc(sizeof(struct ASTNode));
	if (node == NULL)
		return (NULL);
	node->parent = parent;
	node->type = COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->data = (void *)strdup(token->value.word);
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
struct ASTNode	*ast_binaryop(struct TokenQueue *queue, struct ASTNode *parent,
		struct Token *token)
{
	struct ASTNode	*node;

	node = (struct ASTNode *)malloc(sizeof(struct ASTNode));
	if (node == NULL)
		return (NULL);
	node->type = BINARY;
	node->args = NULL;
	node->left = parent;
	node->parent = parent->parent;
	parent->parent->left = node;
	parent->parent = node;
	node->data = (void *)token->value.op;
	if (queue->size > 0)
		node->right = ast_command(queue, node, pop_token(queue));
	else
		node->right = NULL;
	free_token(token);
	return (node);
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
struct ASTNode	*ast_redirection(struct TokenQueue *queue,
		struct ASTNode *parent, struct Token *token)
{
	struct ASTNode	*node;

	node = (struct ASTNode *)malloc(sizeof(struct ASTNode));
	if (node == NULL)
		return (NULL);
	node->type = REDIRECTION;
	node->right = NULL;
	node->left = parent;
	node->parent = parent->parent;
	parent->parent->left = node;
	parent->parent = node;
	node->data = (void *)token->value.op;
	if (queue->size > 0)
		node->args = create_args(queue);
	else
		node->args = NULL;
	free_token(token);
	return (node);
}

/**
 * @brief Creates an Abstract Syntax Tree (AST) from a TokenQueue.
 *

* This function takes a TokenQueue(parsed tokens generated from lexical analysis
-> lexer.c and parsed by parser.c)
 *  as input and constructs tree structure from it.
 * AST is represented byt tree with root node (special type of tree-node)
 * that represents the beggining most upper node of this tree.
 *

* @param queue The TokenQueue containing the tokens representing
commands and operators.
* @return A pointer to the root node of the constructed AST.
*/
struct ASTNode	*create_ast(struct TokenQueue *queue)
{
	struct ASTNode	*root;
	struct ASTNode	*node;
	struct Token	*token;

	root = ast_root();
	node = ast_command(queue, root, pop_token(queue));
	root->left = node;
	while (queue->size > 0)
	{
		token = pop_token(queue);
		if (token->type == TOKEN_OPERATOR)
		{
			if (token->value.op == OP_PIPE || token->value.op == OP_OR
				|| token->value.op == OP_AND)
				node = ast_binaryop(queue, node, token);
			else
				node = ast_redirection(queue, node, token);
		}
		else if (token->type == TOKEN_WORD)
			node = ast_command(queue, node, token);
		printf("the queue size: %zu\n", queue->size);
	}
	return (root);
}
