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

#include "minishell.h"

int	msh_unset(int argc, char **argv, t_env **head)
{
	t_env	*p_prev;
	t_env	*current;
	t_env	*tmp;
	char 	*value;

	printf("unset argc: %i\n");
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
	current = *head;
	value = argv[1];
	if (str_exact_match(current->name, value))
	{
		tmp = head;
		head = current->next;
		free(tmp);
		return (0);
	}
	p_prev = head;
	current = current->next;
	while(str_exact_match(current->name, value))
	{

	}
}
