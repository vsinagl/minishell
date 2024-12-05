/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/27 20:20:30 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Function: create_fd_heredoc
Description: Creates a file descriptor for a heredoc by reading input lines until
the end-of-file (EOF) marker is encountered. Lines are written to a pipe.
Parameters:
  - eof: A string representing the end-of-file marker.
Returns: The read-end file descriptor of the pipe, or -1 on failure.
*/
static int	create_fd_heredoc(char *eof)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (-1);
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

// Function: get_fd
// Description: Opens or creates a file descriptor based on the
// specified redirection type.
// Parameters:
//   - filename: The name of the file to open or create.
//   - nodetype: The type of redirection (e.g., input, output, append, heredoc).
// Returns: The file descriptor, or -1 on failure.
static int	get_fd(char *filename, enum e_nodetype nodetype)
{
	int	fd;

	if (nodetype == REDIRECTION_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (nodetype == REDIRECTION_HEREDOC)
		fd = create_fd_heredoc(filename);
	else if (nodetype == REDIRECTION_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (nodetype == REDIRECTION_IN)
		fd = open(filename, O_RDONLY, 0644);
	else
	{
		ft_fprintf(STDERR_FILENO, "Unsupported redirection type\n");
		return (-1);
	}
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error in oppening file\n");
		return (-1);
	}
	return (fd);
}

/*
@description: Overwrite pipeinfo structure with file descriptors
from file to be redirected
--> overwrite only when parent pipe has -1 value (pipe not defined)
==> this means that we are not overwriting already defined file descriptors
(currently opened files)
*/
t_pipeinfo	update_pipeinfo(t_astnode *node, int file_fd,
		t_pipeinfo parent_pipe, char *file_name)
{
	t_pipeinfo	left_pipe;

	file_fd = get_fd(file_name, node->type);
	left_pipe = init_pipe(parent_pipe.read_fd, parent_pipe.write_fd);
	if ((node->type == REDIRECTION_IN || node->type == REDIRECTION_HEREDOC)
		&& parent_pipe.read_fd == -1)
		left_pipe.read_fd = file_fd;
	else if ((node->type == REDIRECTION_OUT || node->type == REDIRECTION_APPEND)
		&& parent_pipe.write_fd == -1)
		left_pipe.write_fd = file_fd;
	else
		close(file_fd);
	return (left_pipe);
}

static enum e_bool	handle_error(t_astnode *node)
{
	if (node == NULL || is_redirection(node) == FALSE || node->data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Syntax error: EOF not provided\n");
		return (FALSE);
	}
	if (node->left == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Missing left part of redirection\n");
		return (FALSE);
	}
	return (TRUE);
}

// Function: execute_redirection
// Description: Executes a redirection operation based on the AST node type.
// Handle sboth individual and chained redirections,
// including heredoc and append.
// Parameters:
//   - node: The current AST node to process.
//   - parent_pipe: The pipe information from the parent process.
// Returns: 0 on success, 1 on failure.
int	execute_redirection(t_astnode *node, t_pipeinfo parent_pipe)
{
	int				file_fd;
	t_pipeinfo		left_pipe;
	char			*file_name;

	file_fd = -1;
	if (handle_error(node) == FALSE)
		return (1);
	file_name = (char *)node->data;
	left_pipe = update_pipeinfo(node, file_fd, parent_pipe, file_name);
	if (node->left)
	{
		return (execute_node(node->left, left_pipe));
	}
	close(file_fd);
	return (0);
}
