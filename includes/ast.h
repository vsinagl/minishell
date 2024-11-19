/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/05 14:39:14 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdint.h>

// MACROS:
# define MAX_TOKENS 1000
# define MAX_TOKEN_LENGTH 1000

enum	TokenType;
enum	OperatorType;
enum	NodeType;
struct	Token;
struct	TokenQueue;
struct	ASTNode;
struct	PipeInfo;
struct	TokenizeState;
struct	tokenize_data;

struct						tokenize_data
{
	int						token_count;
	int						in_quotes;
	int						in_token;
	int						token_index;
	int						len;
};

struct						TokenizeState
{
	char					**tokens;
	int						token_count;
	int						in_quotes;
	int						in_token;
	int						token_index;
};

struct						ArgSizes
{
	size_t					args_size;
	size_t					args_count;
};

// helper struct for AST tree printing module
struct						QueueNode
{
	struct ASTNode			*node;
	int						level;
	struct QueueNode		*next;
};

enum						NodeType
{
	ROOT = 0,
	COMMAND,
	BINARY,
	REDIRECTION,
};

enum						TokenType
{
	TOKEN_WORD = 0,
	TOKEN_OPERATOR,
	TOKEN_END,
	// ... other types ...
};

enum						OperatorType
{
	OP_PIPE,
	OP_REDIRECT_OUT,
	OP_REDIRECT_IN,
	OP_REDIRECT_APPEND,
	OP_AND,
	OP_OR,
};

struct						Token
{
	enum TokenType			type;
	union
	{
		char				*word;
		enum OperatorType	op;
	} value;
	struct Token			*next;
};

struct						TokenQueue
{
	struct Token			*top;
	size_t					size;
};

struct						ASTNode
{
	enum NodeType			type;
	struct ASTNode			*parent;
	struct ASTNode			*left;
	struct ASTNode			*right;
	void					*data;
	char					**args;
};

/*
	@read_fd: pipe read end file descriptor
	@write_fd: pipe write end file descriptor
	@status: -1 = error, 0 = success
*/
struct						PipeInfo
{
	int						read_fd;
	int						write_fd;
	int						status;
};



int				try_builtin(struct ASTNode *node, int option);

// lexer functions
struct TokenQueue			*tokenizer(char *readedline);
// struct ASTNode				*create_ast(struct TokenQueue *queue);
char						**tokenize(char *input);
struct Token				*pop_token(struct TokenQueue *tokens);
void						free_token(struct Token *token);

// executer functions and piping functions
int							execute_ast(struct ASTNode *root);
int							execute_node_main(struct ASTNode *node);
int							execute_node(struct ASTNode *node,
								struct PipeInfo pipeinfo);
int							execute_pipe(struct ASTNode *node,
								struct PipeInfo parent_pipe);
int							execute_command(struct ASTNode *node,
								struct PipeInfo pipeinfo);
struct PipeInfo				init_pipe(int read_fd, int write_fd);
struct PipeInfo				create_child_pipe(struct PipeInfo pipeinfo,
								int type);
struct PipeInfo				create_empty_pipe(void);
struct PipeInfo				create_pipe(void);
int							my_exec(struct ASTNode *node);

// executer utils
int							ft_strarr_len(char **arr);
void						print_args2(char **args);

// lexer utils
void						free_tokens(char **tokens);
void						print_tokens_str(const char **tokens);
void						print_tokens(struct TokenQueue *tokens);
void						print_token(struct Token *token);

//parser functions
void	free_token_queue(struct TokenQueue *tokens);

// printing ast
void						print_whitespace(int n, char whitespace);
void						print_operator(enum OperatorType op);
void						print_astnode(struct ASTNode *node);
void						print_ast_tree(struct ASTNode *root);

// ast utils
char						*concat_and_free(char *str1, char *str2);
void						free_args(char **args);
char						**create_args(struct TokenQueue *queue);
void						free_ast(struct ASTNode *node);


//feature functions --> delete if not used !
int	is_builtin(char *command);

#endif
