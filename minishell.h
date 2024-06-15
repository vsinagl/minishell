/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:27:15 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/13 16:17:49 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*cmd[1024];
	int		type;
}	t_cmd;

//typedef struct s_redir
//{
//	int		type;
//	char	*file;
//	int		mode;
//	int		fd;
//}	t_redir;

//typedef struct s_pipe
//{
//	int	type;
//	struct cmd *left;
//	struct cmd *right;
//}	t_pipe;

//struct s_slist
//{
//	int	type;
//	struct cmd	*left;
//	struct cmd	*right;
//}	t_list;




t_cmd	ft_parse(char *line);
void	ft_execute(t_cmd command);

#endif