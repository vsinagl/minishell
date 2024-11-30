/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:27:15 by mmarek            #+#    #+#             */
/*   Updated: 2024/11/22 15:22:40 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
// # include <readline/history.h>

# include <sys/types.h>
# include <sys/wait.h>

// our libraries:
# include "../ft_fprintf/ft_fprintf.h"
# include "../get_next_line/get_next_line_bonus.h"
# include "../libft/libft.h"
# include "ast.h"

# define MAX_PATH 2000
# define PROMPT "$ "
# define PROMPT_OK "\033[0;32m"
# define PROMPT_ERROR "\033[0;31m"
# define PROMPT_RESET "\033[0m"
# define PROMPT_USER "\033[34m"

typedef struct s_sig
{
	int						sigint;
	int						sigquit;
	int						exit_status;
	pid_t					pid;
}							t_sig;

typedef struct s_env		t_env;
typedef struct s_shelldata	t_shelldata;
typedef struct s_history	t_history;

// typedef struct	s_TokenizeState t_TokenizeState;
// false = 0, true = 1
enum						e_bool
{
	FALSE,
	TRUE,
};

/*
termcap -> structure for manuipulating with terminal capabality
helps to manipulate with moving cursor, deleting written lines on
terminal etc..
*/
typedef struct s_termcap
{
	char					*del_l;
	char					*move_s;
	char					*buffer;
	struct termios			new_term;
	struct termios			old_term;
}							t_termcap;

/*
main shell data structure that holds all data that are used in shell
*/
typedef struct s_shelldata
{
	t_history				*history;
	t_env					*env;
	int						last_status;
	t_termcap				*termcap;
}							t_shelldata;

typedef struct s_history
{
	char					*data;
	t_history				*prev;
	t_history				*next;
}							t_history;

// helper struct that keep track of tokenizing state variables use in
// tokenize function
struct						s_TokenizeState
{
	char					**tokens;
	int						token_count;
	int						in_quotes;
	int						in_token;
	int						token_index;
	t_shelldata				*data;
};

typedef struct s_tokens
{
	char					**tokens;
	int						count;
}							t_tokens;

/*
enumerate used in get_complete_line function that
symbolize actual completeness of line.
*/
enum						e_linestatus
{
	LINE_COMPLETE,
	LINE_INCOMPLETE_QUOTE,
	LINE_INCOMPLETE_PIPE,
	LINE_INCOMPLETE_BACKSLASH
};

typedef struct s_env
{
	char					*name;
	char					*value;
	t_env					*next;
}							t_env;

typedef struct s_cmd
{
	int						type;
	char					*cmd[10];
	struct s_cmd			*next;
	struct s_cmd			*prev;
}							t_cmd;

typedef struct s_list
{
	int						type;
	char					*cmd[10];
	struct s_list			*next;
	struct s_cmd			*prev;
}							t_list;

typedef struct s_gcl_data
{
	char					*line;
	char					*tmp;
	char					*result;
	enum e_linestatus		status;
}							t_gcl_data;

// void						ft_parse(char *line, char pars, char *arr[],
// 								t_cmd *command);
// void						parse_arr(char *line, char pars, char *arr[]);
// void						ft_execute(t_cmd *command);
// void						call_exec(t_cmd *list);
// void						call_pipe(t_cmd *list, int fdd[2]);
// void						input_pipe(t_cmd *list);
// void						output_pipe(t_cmd *list, int fdd[2]);
// void						middle_pipe(t_cmd *list, int fd[2]);
// void						free_command(t_cmd *cmd);
// char						*get_complete_line(int exit_status);

// tokenization
enum e_bool					tokens_check(t_tokenqueue *tokens);

// builtins
int							msh_echo(int argc, char **argv);
int							msh_pwd(void);
int							msh_cd(int argc, char **argv);
int							msh_export(int argc, char **argv, t_env *head);
int							msh_exit(t_astnode *node);
int							msh_env(t_env *head);
int							msh_clear(int argc);
int							msh_unset(int argc, char **argv, t_env **head);
t_astnode					*ast_root(t_shelldata *data);

// redirections
int							execute_redirection(t_astnode *node,
								t_pipeinfo parent_pipe);
enum e_bool					is_redirection(t_astnode *node);

// enviromental variables functions:
t_env						*env_add(t_env *head, char *name, char *value);
int							env_print(t_env *head);
void						env_free(t_env *head);
char						*env_getvalue(t_env *head, char *name);
t_env						*init_env(void);
void						env_free_struct(t_env *env);

// init
int						init_data(t_shelldata *data);

// signals
void						sig_init(void);
void						setup_signal_handling(void);

//input
char *get_input(t_shelldata *data);

// history

// tokenize
char						**tokenize(char *input, t_shelldata *data);

// parser
t_tokenqueue				*tokenizer(char *readline, t_shelldata *data);

// utils
int							str_exact_match(const char *s1, const char *s2);
enum e_bool					line_ok(char *line);
void	print_info(void);
int	check_verbose(t_shelldata *data);

// history
t_history					*history_add(t_shelldata *data, char *line);
t_history					*move_head(t_history *head, int direction);
int							print_history(t_shelldata *data);
void						free_history(t_shelldata *data);

// handle this later
t_astnode					*create_ast(t_tokenqueue *queue, t_shelldata *data);
void						free_data(t_shelldata *data);

// visual functions
void						print_prompt(int exit_status);

// terminal
void						msh_set_term(struct termios *term);

//exit
void 						exit_program(t_shelldata *data);

#endif
