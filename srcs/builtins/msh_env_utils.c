/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:49:34 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 12:53:19 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_free_struct(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
}

void	env_free(t_env *head)
{
	t_env	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		env_free_struct(tmp);
	}
}

// this functions return the pointer to the value or NULL if value is not find
char	*env_getvalue(t_env *head, char *name)
{
	while (head != NULL)
	{
		if (ft_strncmp(head->name, name, ft_strlen(name)) == 0)
			return ((char *)(head->value));
		head = head->next;
	}
	return (NULL);
}
