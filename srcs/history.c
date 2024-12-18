/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/05 19:58:34 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

t_history	*history_add(t_shelldata *data, char *line)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	new->data = ft_strdup(line);
	if (data->history == NULL)
		new->prev = NULL;
	else
	{
		new->prev = data->history;
		new->prev->next = new;
	}
	new->next = NULL;
	data->history = new;
	return (new);
}

/*
return a pointer to previous or next history node
based on direction option:
0 for previous
1 for next
*/
t_history	*move_head(t_history *head, int direction)
{
	t_history	*current;

	if (head == NULL)
		return (NULL);
	current = head;
	if (direction == 0)
	{
		if (current->prev == NULL)
			return (current);
		else
			return (current->prev);
	}
	else if (direction == 1)
	{
		if (current->next == NULL)
			return (current);
		else
			return (current->next);
	}
	return (NULL);
}

int	print_history(t_shelldata *data)
{
	t_history	*current;
	int			i;

	if (data == NULL)
		return (1);
	i = 0;
	current = data->history;
	while (current != NULL)
	{
		printf("History %i: %s\n", i, current->data);
		current = current->prev;
		i++;
	}
	return (0);
}

void	free_history(t_shelldata *data)
{
	t_history		*tmp;

	while (data->history != NULL)
	{
		tmp = data->history;
		data->history = data->history->prev;
		free(tmp->data);
		free(tmp);
	}
}
