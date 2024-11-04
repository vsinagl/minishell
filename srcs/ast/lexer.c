/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/08/31 17:17:31 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	handle_quotes_and_spaces(const char *str, struct tokenize_data *data,
		int *len, int *i)
{
	if (str[*i] == '"' && !(data->in_quotes))
	{
		data->in_quotes = 1;
		data->in_token = 1;
	}
	else if (str[*i] == '"' && data->in_quotes)
	{
		return (1);
	}
	else if (isspace(str[*i]) && !(data->in_quotes))
	{
		if (data->in_token)
			return (1);
	}
	else
	{
		*len += 1;
		data->in_token = 1;
	}
	return (0);
}

int	token_len(const char *str)
{
	struct tokenize_data	data;
	int						len;
	int						i;

	data.in_quotes = 0;
	data.in_token = 0;
	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (handle_quotes_and_spaces(str, &data, &len, &i))
			break ;
		i++;
	}
	return (len);
}

void	set_outof_token_values(struct TokenizeState *state)
{
	state->in_quotes = 0;
	state->tokens[state->token_count][state->token_index] = '\0';
	state->token_count++;
	state->token_index = 0;
	state->in_token = 0;
}

void	handle_char(struct TokenizeState *state, char c, const char *input,
		int i)
{
	if (c == '"' && !state->in_quotes)
	{
		state->tokens[state->token_count] = malloc(token_len(input + i)
				* sizeof(char) + 1);
		state->in_quotes = 1;
		state->in_token = 1;
	}
	else if (c == '"' && state->in_quotes)
		set_outof_token_values(state);
	else if (isspace(c) && !state->in_quotes)
	{
		if (state->in_token)
			set_outof_token_values(state);
	}
	else
	{
		if (state->in_token == 0)
			state->tokens[state->token_count] = malloc(token_len(input + i)
					* sizeof(char) + 1);
		state->tokens[state->token_count][state->token_index++] = c;
		state->in_token = 1;
	}
}

char	**tokenize(char *input)
{
	struct TokenizeState	state;
	int						i;

	state.tokens = malloc(MAX_TOKENS * sizeof(char *));
	state.token_count = 0;
	state.in_quotes = 0;
	state.in_token = 0;
	state.token_index = 0;
	i = 0;
	while (input[i] != '\0')
	{
		handle_char(&state, input[i], input, i);
		if (state.token_count >= MAX_TOKENS - 1)
			break ;
		i++;
	}
	if (state.in_token)
	{
		state.tokens[state.token_count][state.token_index] = '\0';
		state.token_count++;
	}
	state.tokens[state.token_count] = NULL;
	return (state.tokens);
}
