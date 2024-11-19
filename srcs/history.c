/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2024/06/12 20:25:54 by mmarek            #+#    #+#             */
/*   updated: 2024/11/04 17:41:13 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

t_history	*history_add(t_shelldata *data, char *line)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	new->data = line;
	if (data->history == NULL)
		new->prev = NULL;
	else
		new->prev = data->history;
	data->history = new;
	return (new);
}

void	print_history(t_shelldata *data)
{
	t_history	*current;
	int			i;

	i = 0;
	current = data->history;
	while (current != NULL)
	{
		printf("History %i: %s\n", i, current->data);
		current = current->prev;
		i++;
	}
}

void	free_history(t_shelldata *data)
{
	t_history	*tmp;

	while (data->history != NULL)
	{
		tmp = data->history;
		data->history = data->history->prev;
		free(tmp);
	}
}