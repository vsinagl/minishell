/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:42:49 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 13:44:17 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_ast(t_astnode *node)
{
	if (node == NULL)
		return ;
	if (node->left != NULL)
		free_ast(node->left);
	if (node->right != NULL)
		free_ast(node->right);
	if (node->args != NULL)
		free_args(node->args);
	if (node->type == COMMAND)
	{
		if (node->data != NULL)
			free(node->data);
	}
	free(node);
}
