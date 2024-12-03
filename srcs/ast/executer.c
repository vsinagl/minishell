/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 13:45:14 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

enum e_bool	is_redirection(t_astnode *node)
{
	if (node->type == REDIRECTION_APPEND || node->type == REDIRECTION_IN
		|| node->type == REDIRECTION_OUT || node->type == REDIRECTION_HEREDOC)
		return (TRUE);
	return (FALSE);
}

/*
subroutine for execute_command because norminette s*cks
ARGUMENTS:
@status can be 0 or -1
if status  is -1, it tells function that command was builtin function
(like cd or exit) and was already handled in parent process.
You canot pipe these builtin functions, we are returning error
in this case for pipes !.
*/
int	sub_routine_ec(t_astnode *node, t_pipeinfo pipeinfo, int status)
{
	int	ret_value;

	ret_value = 0;
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
	if (status == -1)
		return (0);
	ret_value = my_exec(node);
	exit(ret_value);
}

/*
@node --> current AST node to be executed
@pipeinfo --> structure that holds file descriptors for pipe
command is executed in child process.
parent process wait for child process to finish and then close it's pipes ends.
*/
int	execute_command(t_astnode *node, t_pipeinfo pipeinfo)
{
	pid_t	pid;
	int		status;

	if (is_builtin((char *)node->data) > 0 && (node->parent->type != BINARY
			&& is_redirection(node->parent) == FALSE))
		return (try_builtin(node, 0));
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		sub_routine_ec(node, pipeinfo, 0);
	waitpid(pid, &status, 0);
	if (pipeinfo.read_fd != -1)
		close(pipeinfo.read_fd);
	if (pipeinfo.write_fd != -1)
		close(pipeinfo.write_fd);
	if (WEXITSTATUS(status))
	{
		return (WEXITSTATUS(status));
	}
	return (0);
}

/*
main executing loop --> base on case (type of AST node),
	function call proper function for handling pipes, commands or redirections
*/
int	execute_node(t_astnode *node, t_pipeinfo pipeinfo)
{
	if (node->type == ROOT)
		node = node->left;
	if (node->type == COMMAND)
		return (execute_command(node, pipeinfo));
	else if (node->type == BINARY)
		return (execute_pipe(node, pipeinfo));
	else if (is_redirection(node) == TRUE)
		return (execute_redirection(node, pipeinfo));
	else
	{
		printf("command i: %i\n", COMMAND);
		ft_fprintf(STDERR_FILENO, "error in execute_node (%i), wrong node\n",
			node->type);
		return (1);
	}
	return (0);
}

/*
stats exectuion of AST
*/
int	execute_node_main(t_astnode *node)
{
	t_pipeinfo	pipeinfo;

	pipeinfo = init_pipe(-1, -1);
	return (execute_node(node, pipeinfo));
}
