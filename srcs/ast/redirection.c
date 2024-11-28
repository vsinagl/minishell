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
static int	create_fd_heredoc(char *eof)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (-1);
	line = readline("heredoc> ");
	while (line != NULL && ft_strcmp(line, eof) != 0)
	{
		ft_putstr_fd(line, pipe_fd[1]);
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	// close(pipe_fd[1]);
	return (pipe_fd[0]);
}


static int	get_fd(char *filename, enum NodeType nodetype)
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
		ft_fprintf(STDERR_FILENO, "Unsuported redirection type\n");
		return (-1);
	}
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error in opening file for redirection\n");
		return (-1);
	}
	return (fd);
}
*/

/*
//working function, but it's too long so i try to refactor it
int	execute_redirection(struct ASTNode *node, struct PipeInfo parent_pipe)
{
	int				file_fd;
	struct PipeInfo	left_pipe;
	char			*file_name;
	int				ret;
		int     pipe_fd[2];
		char    *line;

	file_fd = -1;
	if (node == NULL || is_redirection(node) == FALSE || node->data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Syntax error: EOF not provided\n");
		return (1);
	}
	file_name = (char *)node->data;
	if (node->left && is_redirection(node->left)
		&& node->type == REDIRECTION_HEREDOC)
	{
		if (pipe(pipe_fd) == -1)
			return (-1);
		left_pipe = init_pipe(pipe_fd[0], parent_pipe.write_fd);
		ret = execute_redirection(node->left, left_pipe);
		line = readline("heredoc_end> ");
		while (line != NULL && ft_strcmp(line, file_name) != 0)
		{
			ft_putstr_fd(line, pipe_fd[1]);
			write(pipe_fd[1], "\n", 1);
			free(line);
			line = readline("heredoc_end> ");
		}
		free(line);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		return (ret);
	}
	else
	{
		file_fd = get_fd(file_name, node->type);
		if (file_fd == -1)
			return (1);
		if (node->parent && is_redirection(node->parent))//
			&& node->parent->type != REDIRECTION_HEREDOC)
		{
				if (node->parent->type == REDIRECTION_HEREDOC)
				{
					close(file_fd);
					file_fd = parent_pipe.read_fd;
				}
				else
					file_fd = parent_pipe.write_fd;
		}
		printf("file: %s(%i)\n",file_name, file_fd);
		if (node->type == REDIRECTION_IN || node->type == REDIRECTION_HEREDOC)
		{
			left_pipe = init_pipe(file_fd, parent_pipe.write_fd);
		}
		else
		{
			left_pipe = init_pipe(parent_pipe.read_fd, file_fd);
		}
		ret = 0;
		if (node->left)
		{
			if (is_redirection(node->left))
			{
				ret = execute_redirection(node->left, left_pipe);
			}
			else
			{
				printf("executing with pipe: read: %i || write: %i\n",
					left_pipe.read_fd, left_pipe.write_fd);
				ret = execute_node(node->left, left_pipe);
			}
		}
		close(file_fd);
		return (ret);
	}
}
*/

// working in opposite way
/*
static int	create_fd_heredoc(char *eof)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (-1);
	line = readline("heredoc> ");
	while (line != NULL && ft_strcmp(line, eof) != 0)
	{
		ft_putstr_fd(line, pipe_fd[1]);
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static int	handle_heredoc_append(int read_fd, int write_fd)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	while ((bytes_read = read(read_fd, buffer, sizeof(buffer))) > 0)
	{
		if (write(write_fd, buffer, bytes_read) != bytes_read)
			return (-1);
	}
	return (0);
}

static int	get_fd(char *filename, enum NodeType nodetype)
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
		ft_fprintf(STDERR_FILENO, "Unsuported redirection type\n");
		return (-1);
	}
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error in opening file for redirection\n");
		return (-1);
	}
	return (fd);
}

int	execute_redirection(struct ASTNode *node, struct PipeInfo parent_pipe)
{
	int				file_fd;
	struct PipeInfo	left_pipe;
	char			*file_name;
	int				ret;
	int				heredoc_fd;
	int				append_fd;

	file_fd = -1;
	if (node == NULL || is_redirection(node) == FALSE || node->data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Syntax error: EOF not provided\n");
		return (1);
	}
	file_name = (char *)node->data;
	if (node->type == REDIRECTION_HEREDOC && node->parent
		&& node->parent->type == REDIRECTION_APPEND)
	{
		heredoc_fd = create_fd_heredoc(file_name);
		if (heredoc_fd == -1)
			return (1);
		append_fd = open(node->parent->data, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (append_fd == -1)
		{
			close(heredoc_fd);
			return (1);
		}
		handle_heredoc_append(heredoc_fd, append_fd);
		close(heredoc_fd);
		close(append_fd);
		return (0);
	}
	else
	{
		file_fd = get_fd(file_name, node->type);
		if (file_fd == -1)
			return (1);
		if (node->parent && is_redirection(node->parent))//
			&& node->parent->type != REDIRECTION_HEREDOC)
		{
				if (node->parent->type == REDIRECTION_HEREDOC)
				{
					close(file_fd);
					file_fd = parent_pipe.read_fd;
				}
				else
					file_fd = parent_pipe.write_fd;
		}
		printf("file: %s(%i)\n",file_name, file_fd);
		if (node->type == REDIRECTION_IN || node->type == REDIRECTION_HEREDOC)
		{
			left_pipe = init_pipe(file_fd, parent_pipe.write_fd);
		}
		else
		{
			left_pipe = init_pipe(parent_pipe.read_fd, file_fd);
		}
		ret = 0;
		if (node->left)
		{
			if (is_redirection(node->left))
			{
				ret = execute_redirection(node->left, left_pipe);
			}
			else
			{
				printf("executing with pipe: read: %i || write: %i\n",
					left_pipe.read_fd, left_pipe.write_fd);
				ret = execute_node(node->left, left_pipe);
			}
		}
		close(file_fd);
		return (ret);
	}
}
*/

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
	while ((line = readline("heredoc> ")) != NULL)
	{
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

/*
Function: handle_heredoc_append
Description: Reads data from a heredoc file descriptor and appends it to a specified file.
Parameters:
  - read_fd: The file descriptor to read data from.
  - write_fd: The file descriptor to write data to.
Returns: 0 on success, -1 on failure.
*/

static int	handle_heredoc_append(int read_fd, int write_fd)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	printf("copying, read: %i || write: %i\n", read_fd, write_fd);
	while ((bytes_read = read(read_fd, buffer, sizeof(buffer))) > 0)
	{
		if (write(write_fd, buffer, bytes_read) != bytes_read)
			return (-1);
	}
	return (0);
}

// Function: get_fd
// Description: Opens or creates a file descriptor based on the specified redirection type.
// Parameters:
//   - filename: The name of the file to open or create.
//   - nodetype: The type of redirection (e.g., input, output, append, heredoc).
// Returns: The file descriptor, or -1 on failure.
static int	get_fd(char *filename, enum NodeType nodetype)
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
		ft_fprintf(STDERR_FILENO, "Error opening file for redirection\n");
	return (fd);
}


// Function: execute_heredoc_append
// Description: Handles heredoc followed by append redirection. Reads heredoc data
// and appends it to the specified file.
// Parameters:
//   - node: The current AST node containing redirection information.
// Returns: 0 on success, 1 on failure.
static int	execute_heredoc_append(struct ASTNode *node, struct PipeInfo parent_pipe)
{
	// int	heredoc_fd;
	// int	append_fd;

	// heredoc_fd = create_fd_heredoc((char *)node->data);
	// if (heredoc_fd == -1)
	// 	return (1);
	// append_fd = open(node->parent->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// if (append_fd == -1)
	// {
	// 	close(heredoc_fd);
	// 	return (1);
	// }
	// handle_heredoc_append(heredoc_fd, append_fd);
	// close(heredoc_fd);
	// close(append_fd);
	// return (0);
    int heredoc_fd;
    int append_fd;

    heredoc_fd = create_fd_heredoc((char *)node->data);
    if (heredoc_fd == -1)
        return (1);
    
    append_fd = parent_pipe.write_fd;
    if (append_fd == -1)
    {
        close(heredoc_fd);
        return (1);
    }
    
    handle_heredoc_append(heredoc_fd, append_fd);
    close(heredoc_fd);
    return (0);
}

/*
handle_correct_fd - Handles the file descriptor for a given AST node.
@node: The AST node containing redirection information.
@file_fd: The file descriptor to be handled.
@parent_pipe: The pipe information from the parent node.
@file_name: The name of the file to get the file descriptor for.

This function retrieves the file descriptor for the given file name based
on the node type. If the file descriptor retrieval fails, it returns 1.
If the node has a parent and the parent is a redirection node, it adjusts
the file descriptor based on the type of redirection. For HEREDOC redirection,
it closes the current file descriptor and uses the read end of the parent pipe.
For other redirections, it uses the write end of the parent pipe.

Return: The adjusted file descriptor, or 1 if an error occurs.
 */
static int	handle_correct_fd(struct ASTNode *node, int file_fd,
		struct PipeInfo parent_pipe, char *file_name)
{
	file_fd = get_fd(file_name, node->type);
	if (file_fd == -1)
		return (1);
	// file_fd = handle_parent_fd(node, file_fd, parent_pipe);
	if (node->parent && is_redirection(node->parent))
	{
		if (node->parent->type == REDIRECTION_HEREDOC)
		{
			close(file_fd);
			file_fd = parent_pipe.read_fd;
		}
		else
			file_fd = parent_pipe.write_fd;
	}
	return (file_fd);
}

static enum e_bool	handle_error(struct ASTNode *node)
{
	if (node == NULL || is_redirection(node) == FALSE || node->data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Syntax error: EOF not provided\n");
		return (FALSE);
	}
	return (TRUE);
}

// Function: execute_redirection
// Description: Executes a redirection operation based on the AST node type. Handles
// both individual and chained redirections, including heredoc and append.
// Parameters:
//   - node: The current AST node to process.
//   - parent_pipe: The pipe information from the parent process.
// Returns: 0 on success, 1 on failure.
int	execute_redirection(struct ASTNode *node, struct PipeInfo parent_pipe)
{
	int file_fd;
	struct PipeInfo left_pipe;
	char *file_name;

	if (handle_error(node) == FALSE)
		return (1);
	ft_fprintf(STDOUT_FILENO,"node: %s\n", (char *)node->data);
	file_name = (char *)node->data;
	if (node->type == REDIRECTION_HEREDOC && node->parent
		&& node->parent->type == REDIRECTION_APPEND)
		return (execute_heredoc_append(node, parent_pipe));
	file_fd = handle_correct_fd(node, file_fd, parent_pipe, file_name);
	if (node->type == REDIRECTION_IN || node->type == REDIRECTION_HEREDOC)
		left_pipe = init_pipe(file_fd, parent_pipe.write_fd);
	else
		left_pipe = init_pipe(parent_pipe.read_fd, file_fd);
	if (node->left)
	{

		// if (is_redirection(node->left))
		// 	return (execute_redirection(node->left, left_pipe));
		// else
		{
			printf("executing with pipe: read: %i || write: %i\n",
				left_pipe.read_fd, left_pipe.write_fd);
			return (execute_node(node->left, left_pipe));
		}
	}
	close(file_fd);
	return (0);
}