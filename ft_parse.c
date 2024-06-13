/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/13 10:29:11 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	ft_parse(char *line)
{
	t_command	command;
	int			count;
	char		*delimiter = " ";
	char		*token;

	count = 0;

	token = strtok(line, delimiter);
	while (token != NULL)
	{
		command.flags[count] = strdup(token);
		token = strtok(NULL, delimiter);
		count++;
	}
	command.flags[count] = token;

	//printf ("Command: %s\n", command.command);
	//printf ("Command: %s\n", command.flags[0]);
	//printf ("Command: %s\n", command.flags[1]);
	//printf ("Command: %s\n", command.flags[2]);
	//printf ("Command: %s\n", command.flags[3]);
	//printf ("Command: %s\n", command.flags[4]);


	return (command);
}