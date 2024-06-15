/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:39 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/13 17:08:01 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	return (pid);
}

void	ft_execute(t_cmd command)
{

	//fork
	pid_t	pid, wpid;
	int 	i;

	if (strcmp(command.cmd[0], "cd") == 0)
	{
		chdir(command.cmd[1]);
		//printf("cd command\n");
	}
	else if (strcmp(command.cmd[0], "exit") == 0)
	{
		printf("exit command\n");
	}
	else
	{
		if (fork1() == 0)
		{
			execvp(command.cmd[0], command.cmd);
		}
		wait (0);
	}
	//{
	//		//execute line, create new fork
	//	pid = fork();	//create new fork, execute command, close fork
	//	if (pid == 0)	//Child process
	//	{
	//		execvp(command.flags[0], command.flags);
	//		exit (0);
	//	}
	//	else
	//	{
	//		wpid = wait(NULL);
	//	}
	//}


	//free command
	i = 0;
	while (command.cmd[i] != NULL)
	{
		free(command.cmd[i]);
		i++;
	}

}