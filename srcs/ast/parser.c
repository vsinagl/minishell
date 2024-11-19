/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/04 17:31:06 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

/*
function that pops first element (the first added element) from stack
*/
struct Token	*pop_token(struct TokenQueue *tokens)
{
	struct Token	*token;

	if (tokens->size == 0 || tokens->top == NULL)
		return (NULL);
	token = tokens->top;
	tokens->top = tokens->top->next;
	tokens->size--;
	return (token);
}

void	free_token(struct Token *token)
{
	if (token->type == TOKEN_WORD)
	{
		if (token->value.word != NULL)
			free(token->value.word);
	}
	free(token);
}

void	free_token_queue(struct TokenQueue *tokens)
{
	struct Token	*current;
	struct Token	*next;

	current = tokens->top;
	while (current != NULL)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
	free(tokens);
}

/*
reuturn a operator type from given string token (not a token struct)
*/
enum OperatorType	get_operator_type(const char *token)
{
	if (strcmp(token, "|") == 0)
		return (OP_PIPE);
	if (strcmp(token, ">") == 0)
		return (OP_REDIRECT_OUT);
	if (strcmp(token, "<") == 0)
		return (OP_REDIRECT_IN);
	if (strcmp(token, ">>") == 0)
		return (OP_REDIRECT_APPEND);
	if (strcmp(token, "&&") == 0)
		return (OP_AND);
	if (strcmp(token, "||") == 0)
		return (OP_OR);
	return (-1);
}

/*
function that reciveve string token from lexer and create tokens structure
*/
struct Token	*tokenize_and_identify(const char *str_token)
{
	struct Token		*token;
	enum OperatorType	op_type;

	token = (struct Token *)malloc(sizeof(struct Token));
	op_type = get_operator_type(str_token);
	if ((int)op_type != -1)
	{
		token->type = TOKEN_OPERATOR;
		token->value.op = op_type;
	}
	else
	{
		token->type = TOKEN_WORD;
		token->value.word = strdup(str_token);
	}
	return (token);
}

struct TokenQueue	*init_token_queue(void)
{
	struct TokenQueue	*queue;

	queue = (struct TokenQueue *)malloc(sizeof(struct TokenQueue));
	queue->size = 0;
	queue->top = NULL;
	return (queue);
}

/*
creates a token queue from given array of string tokens
*/
struct TokenQueue	*tokenizer(char *readline)
{
	struct TokenQueue	*tokens;
	struct Token		*token;
	struct Token		*prev;
	char				**str_tokens;
	int					i;

	str_tokens = tokenize(readline);
	tokens = init_token_queue();
	i = 0;
	prev = NULL;
	while (str_tokens[i] != NULL)
	{
		token = tokenize_and_identify(str_tokens[i]);
		free(str_tokens[i]);
		if (tokens->top == NULL)
			tokens->top = token;
		if (prev != NULL)
			prev->next = token;
		prev = token;
		tokens->size++;
		i++;
	}
	free(str_tokens);
	token->next = NULL;
	return (tokens);
}
