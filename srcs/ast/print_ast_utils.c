/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/04 16:11:34by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_whitespace(int n, char whitespace)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("%c", whitespace);
		i++;
	}
}

/*

*/
void	print_operator(enum NodeType op)
{
	if (op == BINARY)
		printf("PIPE");
	else if (op == REDIRECTION_OUT)
		printf("REDIRECT_OUT");
	else if (op == REDIRECTION_IN)
		printf("REDIRECT_IN");
	else if (op == REDIRECTION_APPEND)
		printf("REDIRECT_APPEND");
	else if (op == AND)
		printf("AND");
	else if (op == OR)
		printf("OR");
}

/*
 * Function that print AST node parametetrs (type of Node (binary, command,
		etc..)
 * , data, arguments)
 */
void	print_astnode(struct ASTNode *node)
{
	if (node == NULL)
	{
		printf("NULL");
		return ;
	}
	if (node->type == COMMAND)
	{
		printf("COMMAND: %s ", (char *)node->data);
		if (node->args != NULL)
			print_args2(node->args);
	}
	else if (node->type == BINARY || is_redirection(node) == TRUE)
	{
    	print_operator(node->type);
    	if (is_redirection(node) == TRUE)
		{

			if (node->args != NULL)
        		printf(" %s", (char *)node->args[0]);
		}
	}
	else if (node->type == ROOT)
		printf("ROOT");
}
