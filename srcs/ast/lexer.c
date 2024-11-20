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

// int	handle_quotes_and_spaces(const char *str, struct t_TokenizeState *data,
// 		int *len, int *i)
// {
// 	if (str[*i] == '"' && !(data->in_quotes))
// 	{
// 		data->in_quotes = 1;
// 		data->in_token = 1;
// 	}
// 	else if (str[*i] == '"' && data->in_quotes)
// 	{
// 		return (1);
// 	}
// 	else if (isspace(str[*i]) && !(data->in_quotes))
// 	{
// 		if (data->in_token)
// 			return (1);
// 	}
// 	else
// 	{
// 		*len += 1;
// 		data->in_token = 1;
// 	}
// 	return (0);
// }

// int	token_len(const char *str, struct t_TokenizeState *state)
// {
// 	struct t_TokenizeState	data;
// 	int						len;
// 	int						i;

// 	data.in_quotes = state->in_quotes;
// 	data.in_token = state->in_token;
// 	len = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (handle_quotes_and_spaces(str, &data, &len, &i))
// 			break ;
// 		i++;
// 	}
// 	return (len);
// }

// void	set_outof_token_values(struct t_TokenizeState *state)
// {
// 	state->in_quotes = 0;
// 	state->tokens[state->token_count][state->token_index] = '\0';
// 	state->token_count++;
// 	state->token_index = 0;
// 	state->in_token = 0;
// }

// void handle_dollar(struct t_TokenizeState *state, char *c, char **input, int i)
// {
//     char    *var_name;
//     char    *var_value;
//     int     var_name_len;
//     char    *new_str;
//     char    *new_str2;

//     // Get the length of the variable name after the dollar sign
//     var_name_len = token_len(*input + i + 1, state);
    
//     // Extract the variable name (e.g., "PATH" from "$PATH")
//     var_name = ft_substr(*input, i + 1, var_name_len);
//     if (!var_name) {
//         // Handle error if variable name extraction fails
//         return;
//     }

//     // Look up the variable value in the environment
//     var_value = env_getvalue(state->data->env, var_name);
//     printf("THE VAR_NAME_LEN: '%i'\n", var_name_len);
//     printf("var_name: '%s'\n", var_name);
//     printf("var_value: '%s'\n", var_value ? var_value : "NULL");

//     // If the variable isn't found, replace it with an empty string or keep '$'
//     if (!var_value) {
//         new_str = ft_strjoin(ft_substr(*input, 0, i), "$");
//     } else {
//         new_str = ft_strjoin(ft_substr(*input, 0, i), var_value);
//     }

//     // Now append the rest of the string after the variable
//     new_str2 = ft_strjoin(new_str, *input + i + var_name_len + 1);

//     // Free the old input string and the intermediate new_str
//     free(*input);
//     free(new_str);
//     free(var_name);

//     // Update *input to point to the new string
//     *input = new_str2;

//     // Set the current character for tokenization (not really necessary but keeps consistency)
//     *c = (*input)[i];
// }

// void	handle_char(struct t_TokenizeState *state, char c, char **input, int i)
// {
// 	printf("handling char: '%c'\n", c);
// 	if (c == '$' && (*input)[i + 1] != '?')
// 		handle_dollar(state, &c, input, i);
// 	if (c == '"' && !state->in_quotes)
// 	{
// 		state->tokens[state->token_count] = malloc(token_len(*input + i, state)
// 				* sizeof(char) + 1);
// 		state->in_quotes = 1;
// 		state->in_token = 1;
// 	}
// 	else if (c == '"' && state->in_quotes)
// 		set_outof_token_values(state);
// 	else if (isspace(c) && !state->in_quotes)
// 	{
// 		if (state->in_token)
// 			set_outof_token_values(state);
// 	}
// 	else
// 	{
// 		if (state->in_token == 0)
// 			state->tokens[state->token_count] = malloc(token_len(*input + i,
// 						state) * sizeof(char) + 1);
// 		state->tokens[state->token_count][state->token_index++] = c;
// 		state->in_token = 1;
// 	}
// }

// char	**tokenize(char *input, t_shelldata *data)
// {
// 	struct t_TokenizeState	state;
// 	int						i;

// 	state.tokens = malloc(MAX_TOKENS * sizeof(char *));
// 	state.token_count = 0;
// 	state.in_quotes = 0;
// 	state.in_token = 0;
// 	state.token_index = 0;
// 	state.data = data;
// 	i = 0;
// 	while (input[i] != '\0')
// 	{
// 		handle_char(&state, input[i], &input, i);
// 		if (state.token_count >= MAX_TOKENS - 1)
// 			break ;
// 		i++;
// 	}
// 	if (state.in_token)
// 	{
// 		state.tokens[state.token_count][state.token_index] = '\0';
// 		state.token_count++;
// 	}
// 	state.tokens[state.token_count] = NULL;
// 	return (state.tokens);
// }

char *append_char_to_string(char *str, char c) {
    int len = strlen(str);
    char *new_str = malloc(len + 2);  // +1 for character +1 for null terminator
    if (!new_str) {
        perror("malloc");
        exit(1);
    }
    strcpy(new_str, str);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return new_str;
}

// Retrieve the value of an environment variable from the linked list
// const char *env_getvalue(t_env *env, const char *name) {
//     while (env) {
//         if (strcmp(env->name, name) == 0) {
//             return env->value;
//         }
//         env = env->next;
//     }
//     return NULL;  // If variable not found
// }


// Tokenize function, handling special cases like $VAR, $$, $? and quoted tokens
char **tokenize(char *input, t_shelldata *data) {
    int i = 0;
	int token_count = 0;
    char **tokens = malloc(100 * sizeof(char *));  // Allocate space for 100 tokens

    if (!tokens) {
        perror("malloc");
        exit(1);
    }

    char *current_token = malloc(100);
    if (!current_token) {
        perror("malloc");
        exit(1);
    }
    current_token[0] = '\0';  // Initialize the first token to be empty

    while (input[i] != '\0') {
        char c = input[i];
        if (c == '$') {
            // Handle dollar expansion
            if (input[i + 1] == '$') {
                // Handle $$ -> expand to process ID
                char *pid_str = ft_itoa(getpid());
				char *tmp = current_token;
                current_token = ft_strjoin(current_token, pid_str); 
                free(pid_str);
				free(tmp);
                i += 2;
            } else if (input[i + 1] == '?') {
                // Handle $? -> expand to exit status
                char *exit_status = ft_itoa(data->last_status);
				char *tmp = current_token;
				current_token = ft_strjoin(current_token, exit_status);
				free(tmp);
				free(exit_status);
                // sprintf(exit_status_str, "%d", get_exit_status());
                // current_token = append_char_to_string(current_token, '$');
                // current_token = append_char_to_string(current_token, exit_status_str[0]);
                // free(exit_status_str);
                i += 2;
            } else {
                // Handle $VAR -> expand to environment variable
                int var_name_len = 0;
                while (isalnum(input[i + 1 + var_name_len]) || input[i + 1 + var_name_len] == '_') {
                    var_name_len++;
                }
                if (var_name_len > 0) {
                    char *var_name = ft_substr(input, i + 1, var_name_len);
                    const char *var_value = env_getvalue(data->env, var_name);
					printf("var_value: '%s', var_name: %s\n", var_value, var_name);
                    if (var_value) {
						//here--> append the string, not dupliucate 
                        // current_token = ft_strdup(var_value);
						char *tmp  = current_token;
						current_token = ft_strjoin(current_token, var_value);
						free(tmp);
                    }
                    free(var_name);
                }
				else{
					current_token = append_char_to_string(current_token, c);
				}
                i += var_name_len + 1;
            }
        }
		else if (c == '"') {
            // Handle quoted strings (ignore dollar expansion inside quotes)
            char quote = c;
            i++;
            while (input[i] != quote && input[i] != '\0') {

			if (input[i] == '$') {
                			// Handle $VAR -> expand to environment variable
                			int var_name_len = 0;
                			while (isalnum(input[i + 1 + var_name_len]) || input[i + 1 + var_name_len] == '_') {
                    			var_name_len++;
                			}
                			if (var_name_len > 0) {
                    			char *var_name = ft_substr(input, i + 1, var_name_len);
                    			const char *var_value = env_getvalue(data->env, var_name);
								printf("var_value: '%s', var_name: %s\n", var_value, var_name);
                    			if (var_value) {
									//here--> append the string, not dupliucate 
                        			// current_token = ft_strdup(var_value);
									char *tmp  = current_token;
									current_token = ft_strjoin(current_token, var_value);
									free(tmp);
                    			}
                    			free(var_name);
                			}
                			i += var_name_len + 1;
            			}
						else{
                			current_token = append_char_to_string(current_token, input[i]);
                			i++;
						}
            			}
            i++;  // Skip the closing quote

        }
		else if (c == '\'') {
            // Handle quoted strings (ignore dollar expansion inside quotes)
            char quote = c;
            i++;
            while (input[i] != quote && input[i] != '\0') {

			if (input[i] == '$') {
                			// Handle $VAR -> expand to environment variable
                			int var_name_len = 0;
                			while (isalnum(input[i + 1 + var_name_len]) || input[i + 1 + var_name_len] == '_') {
                    			var_name_len++;
                			}
                			if (var_name_len > 0) {
                    			char *var_name = ft_substr(input, i + 1, var_name_len);
                    			const char *var_value = env_getvalue(data->env, var_name);
								printf("var_value: '%s', var_name: %s\n", var_value, var_name);
                    			if (var_value) {
									//here--> append the string, not dupliucate 
                        			// current_token = ft_strdup(var_value);
									char *tmp  = current_token;
									current_token = ft_strjoin(current_token, var_value);
									free(tmp);
                    			}
                    			free(var_name);
                			}
                			i += var_name_len + 1;
            			}
						else{
                			current_token = append_char_to_string(current_token, input[i]);
                			i++;
						}
            			}
            i++;  // Skip the closing quote

        }
		else if (isspace(c)) {
            // Handle spaces (end of a token)
            if (strlen(current_token) > 0) {
                tokens[token_count++] = current_token;
                current_token = malloc(100);
                if (!current_token) {
                    perror("malloc");
                    exit(1);
                }
                current_token[0] = '\0';  // Reset current token
            }
            i++;
        }
		// else if (!ft_isalnum(c))
		// {
		// 	if (ft_strlen(current_token) > 0) {
		// 		tokens[token_count++] = current_token;
		// 		current_token = malloc(100);
		// 		if (!current_token) {
		// 			perror("malloc");
		// 			exit(1);
		// 		}
		// 		current_token[0] = c;  // Reset current token
		// 		current_token[1] = '\0';  // Reset current token
		// 	}
		// 	i++;
		// }
		else {
            // Handle regular characters
            current_token = append_char_to_string(current_token, c);
            i++;
        }
    }

    // Add the last token if any
    if (strlen(current_token) > 0) {
        tokens[token_count++] = current_token;
    } else {
        free(current_token);
    }

    // Null-terminate the array of tokens
    tokens[token_count] = NULL;
    return tokens;
}