/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:39 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/20 10:31:09 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	return (pid);
}

void	ft_execute(t_cmd *command)
{

	//fork
	pid_t	pid, wpid;
	int 	i;

	if (strcmp(command->cmd[0], "cd") == 0)
	{
		chdir(command->cmd[1]);
		//printf("cd command\n");
	}
	else if (strcmp(command->cmd[0], "exit") == 0)
	{
		printf("exit command\n");
	}
	else
	{
		if (fork1() == 0)
		{
			execvp(command->cmd[0], command->cmd);
		}
		wait (0);
	}

	if (command->next != NULL)
	{
		command = command->next;
		ft_execute(command);
	}

}
