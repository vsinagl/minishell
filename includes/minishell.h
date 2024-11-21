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
# include <signal.h>

# include <readline/readline.h>
// # include <readline/history.h>

# include <sys/types.h>
# include <sys/wait.h>

//our libraries:
# include "../libft/libft.h"
# include "../ft_fprintf/ft_fprintf.h"
# include "ast.h"

# define MAX_PATH 2000
# define PROMPT_MAIN "minishell --> "
# define PROMPT_CONTINUE "> "

extern int g_command_executing;

typedef struct s_env t_env;
typedef struct s_shelldata t_shelldata;
typedef struct s_history t_history;

// typedef struct	s_TokenizeState t_TokenizeState;
//false = 0, true = 1
enum e_bool
{
	FALSE,
	TRUE,
};

/*
main shell data structure that holds all data that are used in shell
*/
typedef struct s_shelldata
{
	t_history	*history;
	t_env		*env;
	int			last_status;
} t_shelldata;

typedef struct s_history{
	char *data;
	t_history *prev;
}	t_history;

//helper struct that keep track of tokenizing state variables use in 
//tokenize function
struct	t_TokenizeState
{
	char			**tokens;
	int				token_count;
	int				in_quotes;
	int				in_token;
	int				token_index;
	t_shelldata		*data;
};

typedef struct s_tokens
{
    char **tokens;
    int count;
} t_tokens;

/*
enumerate used in get_complete_line function that
symbolize actual completeness of line.
*/
enum e_linestatus {
 	LINE_COMPLETE,
    LINE_INCOMPLETE_QUOTE,
    LINE_INCOMPLETE_PIPE,
    LINE_INCOMPLETE_BACKSLASH
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

typedef struct s_gcl_data
{
	char *line;
	char *tmp;
	char *result;
	enum e_linestatus status;
} t_gcl_data;



void	ft_parse(char *line, char pars, char *arr[], t_cmd *command);
void	parse_arr(char *line, char pars, char *arr[]);
void	ft_execute(t_cmd *command);
void	call_exec(t_cmd *list);
void	call_pipe(t_cmd *list, int fdd[2]);
void	input_pipe(t_cmd *list);
void	output_pipe(t_cmd *list, int fdd[2]);
void	middle_pipe(t_cmd *list, int fd[2]);
void	free_command(t_cmd *cmd);
char	*get_complete_line(void);


//builtins
/* echo --nevim jak se presne bude pasovat do echa. Zakladni echo jsem udelal tak ze funguje jako kdyby to byla executable, takze ./echo "ahoj svete" nebo ./echo ahoj svete
* --- proto pouzivam argv a argc jako input parametry.
*/
int		msh_echo(int argc, char **argv);
int		msh_pwd(void);
int		msh_cd(int argc, char **argv);
int		msh_export(int argc, char **argv, t_env **env);
int		msh_exit(struct ASTNode *node);
int		msh_env(t_env *head);
int 	msh_clear();
struct ASTNode	*ast_root(t_shelldata *data);


//enviromental variables functions:
t_env	*env_add(t_env **head, const char *name, const char *value);
int		env_print(t_env *head);
void	env_free(t_env *head);
char	*env_getvalue(t_env *head, char *name);
t_env 	*init_env(void);

//init
void	init_data(t_shelldata *data);

//signals
void	setup_signal_handling(void);
void	signal_handler(int signo);

//history
t_history	*history_add(t_shelldata *data, char *line);
void	print_history(t_shelldata *data);
void	free_history(t_shelldata *data);

//tokenize
char	**tokenize(char *input, t_shelldata *data);

//parser
struct TokenQueue	*tokenizer(char *readline, t_shelldata *data);

//handle this later
t_history *history_add(t_shelldata *data, char *line);
void print_history(t_shelldata *data);
void free_history(t_shelldata *data);
struct ASTNode	*create_ast(struct TokenQueue *queue, t_shelldata *data);
void free_data(t_shelldata *data);

#endif
