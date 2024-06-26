/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:27:15 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/19 23:17:53 by mmarek           ###   ########.fr       */
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
	int				type;
	char			*cmd[10];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_list
{
	int				type;
	char			*cmd[10];
	struct s_list	*next;
	struct s_cmd	*prev;
}	t_list;

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




void	ft_parse(char *line, char pars, char *arr[], t_cmd *command);
void	parse_arr(char *line, char pars, char *arr[]);
void	ft_execute(t_cmd *command);
void	call_exec(t_cmd *list);
void	call_pipe(t_cmd *list, int fdd[2]);
void	input_pipe(t_cmd *list);
void	output_pipe(t_cmd *list, int fdd[2]);
void	middle_pipe(t_cmd *list, int fd[2]);
void	free_command(t_cmd *cmd);

#endif