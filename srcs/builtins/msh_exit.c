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
	t_shelldata *data;

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
	printf("exit\n");
	root = node;
	while(root->type != ROOT)
		root = root->parent;
	data = (t_shelldata *)root->data;
	free_ast(root);
	free_data(data);
	exit(0);
	return(0);
}
