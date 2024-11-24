/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/21 17:00:47 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int msh_exit(struct ASTNode *node)
{
	struct ASTNode *root;

	if (node == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error in msh_exit, ASTNode is (null)\n");
		return (1);
	}
	if (node->data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error in msh_exit, root->data is (null)\n");
		return(1);
	}
	root = node;
	while(root->type != ROOT)
		root = root->parent;
	free_ast(root);
	exit(0);
	return(0);
}
