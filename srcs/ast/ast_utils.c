/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/08/31 17:17:31 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

char	*concat_and_free(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;
	size_t	new_len;
	char	*new_str;

	if (str1 == NULL || str2 == NULL)
	{
		return (NULL);
	}
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	new_len = len1 + len2 + 1;
	new_str = (char *)malloc(new_len * sizeof(char));
	if (new_str == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(new_str, str1, len1 + 1);
	ft_strlcat(new_str, str2, len2 + 1);
	free(str1);
	free(str2);
	return (new_str);
}

struct ASTNode	*ast_root(void)
{
	struct ASTNode	*node;

	node = (struct ASTNode *)malloc(sizeof(struct ASTNode));
	if (node == NULL)
		return (NULL);
	node->type = ROOT;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->data = NULL;
	node->args = NULL;
	return (node);
}

char	**create_args_new(char **original_args, struct ArgSizes *arr_parametrs)
{
	char	**new_args;
	size_t	i;

	arr_parametrs->args_size *= 2;
	i = 0;
	new_args = (char **)realloc(original_args, arr_parametrs->args_size
			* sizeof(char *));
	if (new_args == NULL)
	{
		while (i < arr_parametrs->args_count)
		{
			free(original_args[i]);
			i++;
		}
		free(original_args);
		return (NULL);
	}
	return (new_args);
}

void	free_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	**create_args(struct TokenQueue *queue)
{
	struct Token	*token;
	struct ArgSizes	arr_parametrs;
	char			**args;

	arr_parametrs.args_count = 0;
	arr_parametrs.args_size = 1;
	args = (char **)malloc(arr_parametrs.args_size * sizeof(char *));
	if (args == NULL)
	{
		return (NULL);
	}
	while (queue->size > 0 && queue->top->type == TOKEN_WORD)
	{
		token = pop_token(queue);
		if (arr_parametrs.args_count >= arr_parametrs.args_size)
			args = create_args_new(args, &arr_parametrs);
		args[arr_parametrs.args_count] = strdup(token->value.word);
		if (args[arr_parametrs.args_count] == NULL)
			free_args(args);
		arr_parametrs.args_count++;
		free(token);
	}
	args[arr_parametrs.args_count] = NULL;
	return (args);
}
