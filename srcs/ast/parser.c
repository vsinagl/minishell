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
#include "../../includes/minishell.h"

/*
reuturn a operator type from given string token (not a token struct)
*/
enum e_operatortype	get_operator_type(const char *token)
{
	if (strcmp(token, "|") == 0)
		return (OP_PIPE);
	if (strcmp(token, ">") == 0)
		return (OP_REDIRECT_OUT);
	if (strcmp(token, "<") == 0)
		return (OP_REDIRECT_IN);
	if (strcmp(token, ">>") == 0)
		return (OP_REDIRECT_APPEND);
	if (strcmp(token, "<<") == 0)
		return (OP_HEREDOC);
	if (strcmp(token, "&&") == 0)
		return (OP_AND);
	if (strcmp(token, "||") == 0)
		return (OP_OR);
	return (-1);
}

/*
function that reciveve string token from lexer and create tokens structure
*/
t_token	*tokenize_and_identify(const char *str_token)
{
	t_token				*token;
	enum e_operatortype	op_type;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	op_type = get_operator_type(str_token);
	if ((int)op_type != -1)
	{
		token->type = TOKEN_OPERATOR;
		token->u_value.op = op_type;
	}
	else
	{
		token->type = TOKEN_WORD;
		if (str_token == NULL)
			token->u_value.word = NULL;
		else
			token->u_value.word = ft_strdup(str_token);
	}
	return (token);
}

t_tokenqueue	*init_token_queue(void)
{
	t_tokenqueue	*queue;

	queue = (t_tokenqueue *)malloc(sizeof(t_tokenqueue));
	queue->size = 0;
	queue->top = NULL;
	return (queue);
}

t_tokenqueue	*create_tokenqueue(char **str_tokens)
{
	t_tokenqueue	*tokens;
	t_token			*token;
	t_token			*prev;
	int				i;

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

/*
creates a token queue from given array of string tokens
*/
t_tokenqueue	*tokenizer(char *readline, t_shelldata *data, int verbose)
{
	t_tokenqueue	*tokens;
	char			**str_tokens;

	str_tokens = tokenize(readline, data);
	if (str_tokens == NULL)
		return (NULL);
	if (verbose == 1)
		print_str_tokens(str_tokens);
	tokens = create_tokenqueue(str_tokens);
	if (tokens == NULL)
		return (NULL);
	return (tokens);
}
