/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/27 15:20:37 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"

t_env	*ast_get_env(t_astnode *node)
{
	while (node->type != ROOT)
		node = node->parent;
	return (((t_shelldata *)node->data)->env);
}

t_shelldata	*ast_get_root_data(t_astnode *node)
{
	while (node->type != ROOT)
		node = node->parent;
	return ((t_shelldata *)node->data);
}

char	**prepare_args(t_astnode *node)
{
	char		**args;
	int			i;

	args = (char **)malloc(sizeof(char *) * (ft_strarr_len(node->args) + 2));
	if (args == NULL)
		exit(1);
	args[0] = ft_strdup((char *)node->data);
	i = 1;
	while (node->args != NULL && node->args[i - 1] != NULL)
	{
		args[i] = ft_strdup(node->args[i - 1]);
		i++;
	}
	args[i] = NULL;
	return (args);
}
