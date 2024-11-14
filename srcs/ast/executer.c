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
ARGUMENTS:
@status can be 0 or -1
if status  is -1, it tells function that command was builtin function
(like cd or exit) and was already handled in parent process.
You canot pipe these builtin functions, we are returning error 
in this case for pipes !.
*/
int	sub_routine_ec(struct ASTNode *node, struct PipeInfo pipeinfo, int status)
{
	int		ret_value;

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
	//here logic for command without redirections ?
	if (status == -1)
		exit(0);
	ret_value = my_exec(node);
	printf("RET VALUE: %i\n", ret_value);
	exit(ret_value);
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
	status = 0;
	if (no_fork_builtins(node) == 0)
		status = -1;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		sub_routine_ec(node, pipeinfo, status);
	waitpid(pid, &status, 0);
	if (pipeinfo.read_fd != -1)
		close(pipeinfo.read_fd);
	if (pipeinfo.write_fd != -1)
		close(pipeinfo.write_fd);
	if (status != 0)
		return (status);
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
		exit(16);
	}
	else
	{
		printf("command i: %i\n", COMMAND);
		ft_fprintf(STDERR_FILENO, "error in execute_node (%i), wrong node\n", node->type);	
		return (1);
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
