/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/08/31 17:17:31 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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
void	print_operator(enum OperatorType op)
{
	if (op == OP_PIPE)
		printf("PIPE");
	else if (op == OP_REDIRECT_OUT)
		printf("REDIRECT_OUT");
	else if (op == OP_REDIRECT_IN)
		printf("REDIRECT_IN");
	else if (op == OP_REDIRECT_APPEND)
		printf("REDIRECT_APPEND");
	else if (op == OP_AND)
		printf("AND");
	else if (op == OP_OR)
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
		printf("COMMAND: %s", (char *)node->data);
		printf(" %s", (char *)node->args[0]);
	}
	else if (node->type == ARGUMENT)
	{
		printf("ARGUMENT: %s", (char *)node->data);
	}
	else if (node->type == BINARY || node->type == REDIRECTION)
	{
		print_operator((enum OperatorType)node->data);
		if (node->type == REDIRECTION)
			printf(" %s", (char *)node->args[0]);
	}
	else if (node->type == ROOT)
		printf("ROOT");
}
