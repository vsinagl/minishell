/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/08/31 17:17:31 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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
		printf("value word: %s\n", token->value.word);
		if (token->value.word != NULL)
			free(token->value.word);
	}
	free(token);
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
	if (op_type != -1)
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

/*
creates a token queue from given array of string tokens
*/
struct TokenQueue	*tokenizer(const char **str_tokens)
{
	struct TokenQueue	*tokens;
	struct Token		*token;
	struct Token		*prev;
	int					i;

	tokens = (struct TokenQueue *)malloc(sizeof(struct TokenQueue));
	tokens->size = 0;
	tokens->top = NULL;
	i = 0;
	prev = NULL;
	while (str_tokens[i] != NULL)
	{
		token = tokenize_and_identify(str_tokens[i]);
		if (tokens->top == NULL)
			tokens->top = token;
		if (prev != NULL)
			prev->next = token;
		prev = token;
		tokens->size++;
		i++;
	}
	token->next = NULL;
	return (tokens);
}
