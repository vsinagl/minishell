/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:46:31 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 14:05:17 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"

static int	handle_double_quotes(const char *input, int i, char **current_token,
		t_shelldata *data)
{
	int	j;

	j = 1;
	while (input[i + j] != '"' && input[i + j] != '\0')
	{
		if (input[i + j] == '$')
			j += handle_dollar_expansion(input, i + j, current_token, data);
		else
		{
			(*current_token) = append_char_to_string((*current_token), input[i
					+ j]);
			j++;
		}
	}
	if (is_string_operator(*current_token) == TRUE && (input[i + j + 1] == '\0'
			|| input[i + j + 1] == ' '))
		(*current_token) = append_char_to_string((*current_token), ' ');
	return (j + 1);
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
		return (handle_double_quotes(input, i, current_token, data));
	else
	{
		while (input[i + j] != '\'' && input[i + j] != '\0')
		{
			(*current_token) = append_char_to_string((*current_token), input[i
					+ j]);
			j++;
		}
	}
	if (is_string_operator(*current_token) == TRUE && (input[i + j + 1] == '\0'
			|| input[i + j + 1] == ' '))
		(*current_token) = append_char_to_string((*current_token), ' ');
	return (j + 1);
}

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
	free(str);
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
