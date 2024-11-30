/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/04 16:01:43 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// apend a character to string, it's basically same as ft_strjoin but we are
// joining characetr to string instead of string to string
// it creates a new string, allocates memory for it, coppy the original string
// append character and then free string
char	*append_char_to_string(char *str, char c)
{
	int		len;
	char	*new_str;

	len = strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		perror("malloc");
		exit(1);
	}
	strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

// handle spaces --> end of token
int	end_of_token(const char *input, int i, char **current_token,
		t_tokens *tokens)
{
	int	j;

	j = 1;
	while (input[i + j] == ' ')
		j++;
	if (ft_strlen(*current_token) > 0)
	{
		tokens->tokens[tokens->count++] = *current_token;
		*current_token = (char *)malloc(100);
		if (!current_token)
		{
			ft_fprintf(STDERR_FILENO, "malloc error in end_of_token\n");
			exit(1);
		}
		(*current_token)[0] = '\0';
	}
	return (j);
}

/*
handle enviroment variable exapnsion. Append variable value instead of $VAR (variable name with $ sign)
to current processed token and return the length of characters that were processed
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

/*
handle double quotes "" "
- simple append char to token until we find second quote :)
- if we find $, we simply call handle dollar expansion and
append the result to current token
*/
int	handle_quotes(const char *input, int i, char **current_token,
		t_shelldata *data)
{
	int	j;

	j = 1;
	if (input[i] == '"')
	{
		while (input[i + j] != '"' && input[i + j] != '\0')
		{
			if (input[i + j] == '$')
				j += handle_dollar_expansion(input, i + j, current_token, data);
			else
			{
				(*current_token) = append_char_to_string((*current_token),
						input[i + j]);
				j++;
			}
		}
	}
	else
	{
		while (input[i + j] != '\'' && input[i + j] != '\0')
		{
			(*current_token) = append_char_to_string((*current_token), input[i
					+ j]);
			j++;
		}
	}
	// printf("len cur token: %lu\n", strlen(*current_token));
	// printf("test function: %i\n", is_string_operator(*current_token));
	printf("input[i + j + 1] is: %c\n", input[i + j + 1]);
	if (is_string_operator(*current_token) == TRUE && (input[i + j + 1] == '\0' || input[i + j + 1] == ' '))
		(*current_token) = append_char_to_string((*current_token), ' ');
	// printf("j is: %i\n", j);
	// printf("input[i + j] is: %c\n", input[i + j]);
	// printf("*current_token is: %s\n", *current_token);
	return (j + 1);
}

char	*tokenize_init(t_tokens *tokens)
{
	char	*current_token;

	if (tokens == NULL)
		return (NULL);
	tokens->count = 0;
	tokens->tokens = (char **)malloc(MAX_TOKENS * sizeof(char *));
	if (tokens->tokens == NULL)
	{
		ft_fprintf(STDERR_FILENO, "malloc error in tokenize_init (lexer.c)\n");
		return (NULL);
	}
	current_token = ft_strdup("");
	if (current_token == NULL)
	{
		ft_fprintf(STDERR_FILENO, "malloc error in tokenize_init (lexer.c)\n");
		return (NULL);
	}
	return (current_token);
}

// finish the token array and assure that
// final array of token is properly terminatd
// this broke a tokenize function and now tokenize function is much less readable
// however, it was neccasary to do it beauces of norminette
void	handle_final_token(char **current_token, t_tokens *tokens)
{
	if (ft_strlen(*current_token) > 0)
		tokens->tokens[tokens->count++] = *current_token;
	else
		free(*current_token);
	tokens->tokens[tokens->count] = NULL;
}

// Tokenize function, handling special cases like $VAR, $$, $? and quoted tokens
char	**tokenize(char *input, t_shelldata *data)
{
	t_tokens tokens;
	char *current_token;
	int i = 0;

	current_token = tokenize_init(&tokens);
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
		else
		{
			current_token = append_char_to_string(current_token, input[i]);
			i++;
		}
	}
	handle_final_token(&current_token, &tokens);
	return (tokens.tokens);
}