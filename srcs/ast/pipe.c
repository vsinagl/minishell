/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/04 16:01:57 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ast.h"

struct PipeInfo	init_pipe(int read_fd, int write_fd)
{
	struct PipeInfo	pipe;

	pipe.read_fd = read_fd;
	pipe.write_fd = write_fd;
	pipe.status = 0;
	return (pipe);
}

/*
creating and handling pipes. Pipes are handled according to parent_pipe and
left child of current root.
*/
int	execute_pipe(struct ASTNode *node, struct PipeInfo parent_pipe)
{
	int				pipe_fd[2];
	struct PipeInfo	left_pipe;
	struct PipeInfo	right_pipe;
	int				status;

	if (node == NULL || node->type != BINARY)
	{
		ft_fprintf(STDERR_FILENO, "Wrong node pass to execute_pipe/pipe.c\n");
		return(1);
	}
	if (pipe(pipe_fd) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error in creating pipe-> pipe.c/execute_pipe\n");
		return(1);
	}
	left_pipe = init_pipe(-1, pipe_fd[1]);
	right_pipe = init_pipe(pipe_fd[0], parent_pipe.write_fd);
	pid_t pid_left = fork();
	if (pid_left == -1)
		return (1);
	if (pid_left == 0)
	{
		close(pipe_fd[0]);
		exit(execute_node(node->left, left_pipe));
	}
	pid_t pid_right = fork();
	if (pid_right == -1)
		return (1);
	if (pid_right == 0)
	{
		close(pipe_fd[1]);
		exit(execute_node(node->right, right_pipe));
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return status;
	// printf("executiing left node: %s\n", (char*)(node->left->data));
	// if (execute_node(node->left, left_pipe))
	// 	return (1);
	// printf("executing right node: %s\n", (char*)(node->right->data));
	// if (execute_node(node->right, right_pipe))
	//  	return (2);
	// return (0);
}
