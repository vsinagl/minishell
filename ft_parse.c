/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/15 09:41:21 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	ft_parse(char *line)
{
	t_cmd		command;
	int			count;
	char		*delimiter = " ";
	char		*token;

	count = 0;

	token = strtok(line, delimiter);
	while (token != NULL)
	{
		command.cmd[count] = strdup(token);
		token = strtok(NULL, delimiter);
		count++;
	}
	command.cmd[count] = token;
	command.type = 1;

	return (command);
}