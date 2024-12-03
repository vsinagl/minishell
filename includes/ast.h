/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 13:58:47 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../libft/libft.h"
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// MACROS:
# define MAX_TOKENS 1000
# define MAX_TOKEN_LENGTH 1000

typedef struct s_shelldata t_shelldata;

// enum	e_tokentype;
// enum	e_operatortype;
// enum	e_nodetype;
// struct	s_tokenqueue;
// struct	s_astnode;
// struct	s_pipeinfo;
// struct t_tokenize_data;

typedef struct s_ArgSizes
{
	size_t					args_size;
	size_t					args_count;
}							t_argsizes;

enum						e_nodetype
{
	ROOT = 0,
	COMMAND,
	BINARY,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	REDIRECTION_APPEND,
	REDIRECTION_HEREDOC,
	AND,
	OR,
};

enum						e_tokentype
{
	TOKEN_WORD = 0,
	TOKEN_OPERATOR,
	TOKEN_END,
};

enum						e_operatortype
{
	OP_PIPE,
	OP_REDIRECT_OUT,
	OP_REDIRECT_IN,
	OP_REDIRECT_APPEND,
	OP_HEREDOC,
	OP_AND,
	OP_OR,
};

typedef struct s_token
{
	enum e_tokentype		type;
	union
	{
		char				*word;
		enum e_operatortype	op;
	} u_value;
	struct s_token			*next;
}							t_token;

typedef struct s_tokenqueue
{
	t_token					*top;
	size_t					size;
}							t_tokenqueue;

typedef struct s_astnode
{
	enum e_nodetype			type;
	struct s_astnode		*parent;
	struct s_astnode		*left;
	struct s_astnode		*right;
	void					*data;
	char					**args;
}							t_astnode;

typedef struct s_queuenode
{
	t_astnode				*node;
	int						level;
	struct s_queuenode		*next;
}							t_queuenode;

/*
	@read_fd: pipe read end file descriptor
	@write_fd: pipe write end file descriptor
	@status: -1 = error, 0 = success
*/
typedef struct s_pipeinfo
{
	int						read_fd;
	int						write_fd;
	int						status;
}							t_pipeinfo;

typedef struct s_tokens
{
	char					**tokens;
	int						count;
}							t_tokens;

// executer functions and piping functions
int							execute_ast(t_astnode *root);
int							execute_node_main(t_astnode *node);
int							execute_node(t_astnode *node, t_pipeinfo pipeinfo);
int							execute_pipe(t_astnode *node,
								t_pipeinfo parent_pipe);
int							execute_command(t_astnode *node,
								t_pipeinfo pipeinfo);
t_pipeinfo					init_pipe(int read_fd, int write_fd);
t_pipeinfo					create_child_pipe(t_pipeinfo pipeinfo, int type);
t_pipeinfo					create_empty_pipe(void);
t_pipeinfo					create_pipe(void);
int							my_exec(t_astnode *node);

// executer utils
int							ft_strarr_len(char **arr);
void						print_args2(char **args);

// lexer utils
void						free_tokens(char **tokens);
void						print_str_tokens(char **tokens);
void						print_tokens(t_tokenqueue *tokens);
void						print_token(t_token *token);
int							ft_tokenlen(char **tokens);
enum e_bool					is_pipe_redirection(char c);
char						*append_char_to_string(char *str, char c);
int							end_of_token(const char *input, int i,
								char **current_token, t_tokens *tokens);
int							handle_quotes(const char *input, int i,
								char **current_token, t_shelldata *data);
char						*tokenize_init(t_tokens *tokens);

// parser functions
void						free_token_queue(t_tokenqueue *tokens);
enum e_operatortype			get_operator_type(const char *token);

// printing ast
void						print_whitespace(int n, char whitespace);
void						print_astnode(t_astnode *node);
void						print_ast_tree(t_astnode *root);

// ast utils
char						*concat_and_free(char *str1, char *str2);
void						free_args(char **args);
char						**create_args(t_tokenqueue *queue);
void						free_ast(t_astnode *node);

// utils
int							is_builtin(char *command);
int							try_builtin(t_astnode *node, int option);
t_token						*pop_token(t_tokenqueue *tokens);
void						free_token(t_token *token);
enum e_bool					is_string_operator(char *str);
enum e_bool					is_char_operator(char c);

#endif
