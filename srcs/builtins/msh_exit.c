/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 12:38:46 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_exit(t_astnode *node, char **args)
{
	t_astnode	*root;
	t_shelldata	*data;

	if (node == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error in msh_exit, ASTNode is (null)\n");
		return (1);
	}
	if (node->data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error in msh_exit, root->data is (null)\n");
		return (1);
	}
	ft_fprintf(STDOUT_FILENO, "exit");
	root = node;
	while (root->type != ROOT)
		root = root->parent;
	data = (t_shelldata *)root->data;
	free_ast(root);
	free_args(args);
	exit_program(data);
	exit(1);
	return (1);
}
