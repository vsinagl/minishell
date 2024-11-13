/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/04 16:01:35 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
subroutine for execute_command because norminette s*cks
*/
int	sub_routine_ec(struct ASTNode *node, struct PipeInfo pipeinfo)
{
	if (pipeinfo.read_fd != -1)
	{
		dup2(pipeinfo.read_fd, STDIN_FILENO);
		close(pipeinfo.read_fd);
	}
	if (pipeinfo.write_fd != -1)
	{
		dup2(pipeinfo.write_fd, STDOUT_FILENO);
		close(pipeinfo.write_fd);
	}
	if (my_exec(node) != 0)
	{
		exit(-1);
	}
	exit(-2);
}

/*
@node --> current AST node to be executed
@pipeinfo --> structure that holds file descriptors for pipe
command is executed in child process.
parent process wait for child process to finish and then close it's pipes ends.
*/
int	execute_command(struct ASTNode *node, struct PipeInfo pipeinfo)
{
	pid_t	pid;
	int		status;

	if (node == NULL || node->type != COMMAND)
	{
		perror("error in execute_command, wrong node\n");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork not succesfull:");
		exit(1);
	}
	if (pid == 0)
		sub_routine_ec(node, pipeinfo);
	waitpid(pid, &status, 0);
	if (status != 0)
		return (status);
	if (pipeinfo.read_fd != -1)
		close(pipeinfo.read_fd);
	if (pipeinfo.write_fd != -1)
		close(pipeinfo.write_fd);
	return (0);
}

/*
main executing loop --> base on case (type of AST node),
	function call proper function for handling pipes, commands or redirections
*/
int	execute_node(struct ASTNode *node, struct PipeInfo pipeinfo)
{
	if (node->type == ROOT)
		node = node->left;
	if (node->type == COMMAND)
		return (execute_command(node, pipeinfo));
	else if (node->type == BINARY)
		return (execute_pipe(node, pipeinfo));
	else if (node->type == REDIRECTION)
	{
		perror("error in execute_node, rediretion not supported yet\n");
		return (-1);
	}
	else
	{
		printf("command i: %i\n", COMMAND);
		ft_fprintf(STDERR_FILENO, "error in execute_node (%i), wrong node\n", node->type);	
		return (-1);
	}
	return (0);
}

/*
stats exectuion of AST
*/
int	execute_node_main(struct ASTNode *node)
{
	struct PipeInfo	pipeinfo;

	pipeinfo = init_pipe(-1, -1);
	return (execute_node(node, pipeinfo));
}
