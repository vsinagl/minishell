/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:45:43 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/20 10:31:09 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	call_exec(t_cmd *list)
{
	if (list != NULL)
	{	if (fork() == 0)
			execvp(list->cmd[0], list->cmd);
		wait(NULL);
		list = list->next;
		if (list != NULL)
			call_exec(list);
	}
}

/** Call input pipe */
void	input_pipe(t_cmd *list)
{
	//if only one command, no pipe
	if (list->next == NULL)
	{
		call_exec(list);
		return ;
	}

	int	fd[2];
	pipe(fd);
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execvp(list->cmd[0], list->cmd);
	}
	list = list->next;

	if (list->next == NULL)
		output_pipe(list, fd);
	else
		middle_pipe(list, fd);
}

/** Call middle pipe */
void	middle_pipe(t_cmd *list, int fd[2])
{
	int	fd2[2];

	pipe(fd2);
	if (fork() == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		dup2(fd2[1], STDOUT_FILENO);
		close(fd2[0]);
		close(fd2[1]);
		execvp(list->cmd[0], list->cmd);
	}
	close(fd[0]);
	close(fd[1]);
	list = list->next;

	if (list->next == NULL)
		output_pipe(list, fd2);
	else
		middle_pipe(list, fd2);
}


/** Call output pipe */
void	output_pipe(t_cmd *list, int fdd[2])
{
	if (fork() == 0)
		{
			dup2(fdd[0], STDIN_FILENO);
			close(fdd[0]);
			close(fdd[1]);
			printf("Here is the output pipe\n");
			execvp(list->cmd[0], list->cmd);
			//execlp("wc", "wc", "-l", NULL);
		}
		close(fdd[0]);
		close(fdd[1]);
		wait (NULL);
}


