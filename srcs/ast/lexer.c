/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 14:08:12 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
handle enviroment variable exapnsion. Append variable value instead
of $VAR (variable name with $ sign)
to current processed token and return the length of characters
that were processed
which is equal to length of variable name + 1 (for $ sign)
*/
int	handle_env_expansion(const char *input, int i, char **current_token,
		t_shelldata *data)
{
	int			var_name_len;
	char		*var_name;
	const char	*var_value;
	char		*tmp;

	var_name_len = 0;
	while (isalnum(input[i + 1 + var_name_len]) || input[i + 1
			+ var_name_len] == '_')
		var_name_len++;
	if (var_name_len > 0)
	{
		var_name = ft_substr(input, i + 1, var_name_len);
		var_value = env_getvalue(data->env, var_name);
		if (var_value)
		{
			tmp = *current_token;
			*current_token = ft_strjoin(*current_token, var_value);
			free(tmp);
		}
		free(var_name);
	}
	else
		*current_token = append_char_to_string(*current_token, '$');
	return (var_name_len + 1);
}

/*
Main dollar handling function:
- if $$ -> expand to process ID
- if $? -> expand to exit status
- if $VAR -> expand to environment variable
it returns the number of characters processed
 */
int	handle_dollar_expansion(const char *input, int i, char **current_token,
		t_shelldata *data)
{
	char	*help_str;
	char	*tmp;

	tmp = *current_token;
	if (input[i + 1] == '$')
	{
		help_str = ft_itoa(getpid());
		(*current_token) = ft_strjoin((*current_token), help_str);
		free(help_str);
		free(tmp);
		return (2);
	}
	else if (input[i + 1] == '?')
	{
		help_str = ft_itoa(data->last_status);
		(*current_token) = ft_strjoin((*current_token), help_str);
		free(help_str);
		free(tmp);
		return (2);
	}
	else
		return (handle_env_expansion(input, i, current_token, data));
}

// finish the token array and assure that
// final array of token is properly terminatd
// this broke a tokenize function and now tokenize function
// is much less readable
// however, it was neccasary to do it beauces of norminette
void	handle_final_token(char **current_token, t_tokens *tokens)
{
	if (ft_strlen(*current_token) > 0)
		tokens->tokens[tokens->count++] = *current_token;
	else
		free(*current_token);
	tokens->tokens[tokens->count] = NULL;
}

int	handle_operator(const char *input, int i, char **current_token,
		t_tokens *tokens)
{
	char	operator;
	int		j;

	operator = input[i];
	end_of_token(input, i, current_token, tokens);
	j = 0;
	while ((input[i] == operator) && (j < 2))
	{
		*(current_token) = append_char_to_string(*(current_token), input[i]);
		i++;
		j++;
	}
	end_of_token(input, i, current_token, tokens);
	return (j);
}

// Tokenize function, handling special cases like $VAR, $$, $? and quoted tokens
char	**tokenize(char *input, t_shelldata *data)
{
	t_tokens	tokens;
	char		*current_token;
	int			i;

	current_token = tokenize_init(&tokens);
	i = 0;
	if (current_token == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			i += handle_dollar_expansion(input, i, &current_token, data);
		else if (input[i] == '"' || input[i] == '\'')
			i += handle_quotes(input, i, &current_token, data);
		else if (isspace(input[i]))
			i += end_of_token(input, i, &current_token, &tokens);
		else if (is_char_operator(input[i]))
			i += handle_operator(input, i, &current_token, &tokens);
		else
		{
			current_token = append_char_to_string(current_token, input[i]);
			i++;
		}
	}
	handle_final_token(&current_token, &tokens);
	if (tokens.count == 0 && tokens.tokens[0] == NULL)
		return (NULL);
	return (tokens.tokens);
}
