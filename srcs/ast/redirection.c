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


static int create_fd_heredoc(char *eof)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (-1);
	line = readline("heredoc> ");
	while(line != NULL && ft_strcmp(line, eof) != 0)
	{
		ft_putstr_fd(line, pipe_fd[1]);
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	close(pipe_fd[1]);
	return(pipe_fd[0]);
}



static int get_fd(char *filename, enum NodeType nodetype)
{
	int		fd;

	if (nodetype == REDIRECTION_OUT)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (nodetype == REDIRECTION_HEREDOC)
		fd = create_fd_heredoc(filename);
    else if (nodetype == REDIRECTION_APPEND)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND);
    else if (nodetype == REDIRECTION_IN)
        fd = open(filename, O_RDONLY);
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

/*
fuction that handle execution of redirections.
*/
int	execute_redirection(struct ASTNode *node, struct PipeInfo parent_pipe)
{
	int				file_fd;
	struct PipeInfo	left_pipe;
	char			*file_name;

	if (node == NULL || is_redirection(node) == FALSE || node->data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Syntax error: EOF not provided\n");
		return (1);
	}
	file_name = (char *)node->data;
	file_fd = get_fd(file_name, node->type);
	if (file_fd == -1)
		return (1);
    if (node->type == REDIRECTION_IN || node->type == REDIRECTION_HEREDOC)
		left_pipe = init_pipe(file_fd, parent_pipe.write_fd);
	else
        left_pipe = init_pipe(parent_pipe.read_fd, file_fd);
	if (execute_node(node->left, left_pipe))
	{
		close(file_fd);
		return (1);
    }
    close(file_fd);
    return (0);
}
