/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:07:42 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/22 15:32:58 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
function to unset an enviroment variable
- if variable is not foud, return: 0
-  in case of error: return 1

*/
static void	search_through_envlist(t_env **head, char *value)
{
	t_env	*p_prev;
	t_env	*current;
	t_env	*tmp;

	current = *head;
	if (str_exact_match(current->name, value))
	{
		*head = current->next;
		free(current);
		return ;
	}
	p_prev = current;
	current = current->next;
	while(current != NULL)
	{
		if (str_exact_match(current->name, value))
		{
			tmp = current;
			p_prev->next = current->next;
			free(tmp);
			return ;
		}
		p_prev = current;
		current = current->next;
	}
}


static void	arg_loop(int argc, char **argv, t_env **head)
{
	int 	i;
	char	*value;

	i = 1;
	while (i < argc)
	{
		value = argv[i];
		search_through_envlist(head, value);
		i++;
	}
}

int	msh_unset(int argc, char **argv, t_env **head)
{
	if (argc <= 1)
	{
		ft_fprintf(STDERR_FILENO, "unset: not enough arguments\n");
		return (1);
	}
	if (head == NULL)
	{
		ft_fprintf(STDERR_FILENO, "unset: pointer to t_env * is (null)\n");
		return (1);
	}
	arg_loop(argc, argv, head);
	return (0);
}
