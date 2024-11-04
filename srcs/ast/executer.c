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

#include "../../includes/ast.h"

/*
@node --> node to execute
function that prepare arguments for execve function and execute this function
*/
int	my_exec(struct ASTNode *node)
{
	char	**args;
	char	*command;
	int		i;

	command = ft_strjoin("/bin/", (char *)node->data);
	args = (char **)malloc(sizeof(char *) * (ft_strarr_len(node->args) + 2));
	if (args == NULL)
	{
		perror("malloc");
		exit(1);
	}
	args[0] = command;
	i = 1;
	while (node->args[i - 1] != NULL)
	{
		args[i] = node->args[i - 1];
		i++;
	}
	args[i] = NULL;
	execve(command, args, NULL);
	free(args);
	return (0);
}

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
		perror("my_exec function error");
		exit(1);
	}
	exit(1);
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

	if (node == NULL || node->type != COMMAND)
	{
		perror("error in execute_command, wrong node\n");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		sub_routine_ec(node, pipeinfo);
	waitpid(pid, NULL, 0);
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
		perror("error in execute_node, wrong node\n");
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
