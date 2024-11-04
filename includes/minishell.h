/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:27:15 by mmarek            #+#    #+#             */
/*   Updated: 2024/11/04 16:00:38 by vsinagl          ###   ########.fr       */
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

//our libraries:
# include "../libft/libft.h"
# include "ast.h"
typedef struct s_env t_env;
//false = 0, true = 1
enum e_bool
{
	FALSE,
	TRUE,
};

typedef struct s_env
{
	const char	*name;
	const char	*value;
	t_env	*next;
}	t_env;


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


//builtins
/* echo --nevim jak se presne bude pasovat do echa. Zakladni echo jsem udelal tak ze funguje jako kdyby to byla executable, takze ./echo "ahoj svete" nebo ./echo ahoj svete
* --- proto pouzivam argv a argc jako input parametry.
*/
int		msh_echo(int argc, char **argv);
int		msh_pwd(void);
int		msh_cd(int argc, char **argv);
int		msh_export(int argc, char **argv, t_env **env);
int 	msh_exit(int argc, char **argv);
int		msh_env(t_env *head);


//enviromental variables functions:
t_env	*env_add(t_env **head, const char *name, const char *value);
int		env_print(t_env *head);
void	env_free(t_env *head);
char	*env_getvalue(t_env *head, char *name);

#endif
