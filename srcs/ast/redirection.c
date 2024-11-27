/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/27 18:37:17 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	close(pipe_fd[1]);
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

int	execute_redirection(struct ASTNode *node, struct PipeInfo parent_pipe)
{
	int				file_fd;
	struct PipeInfo	left_pipe;
	char			*file_name;
	int				ret;

	file_fd = -1;
	if (node == NULL || is_redirection(node) == FALSE || node->data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Syntax error: EOF not provided\n");
		return (1);
	}
	file_name = (char *)node->data;
	file_fd = get_fd(file_name, node->type);
	if (file_fd == -1)
		return (1);
	if (node->parent && is_redirection(node->parent))
	{
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
