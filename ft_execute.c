/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:39 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/13 10:44:17 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_command command)
{

	//fork
	pid_t	pid, wpid;
	int 	i;


	//execute line, create new fork
	pid = fork();	//create new fork, execute command, close fork
	if (pid == 0)	//Child process
	{
		execvp(command.flags[0], command.flags);
		exit (0);
	}
	else
	{
		wpid = wait(NULL);
	}

	//free command
	i = 0;
	while (command.flags[i] != NULL)
	{
		free(command.flags[i]);
		i++;
	}

}