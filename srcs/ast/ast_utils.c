/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/22 07:42:39 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ast.h"

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

struct ASTNode	*ast_root(t_shelldata *data)
{
	struct ASTNode	*node;

	node = (struct ASTNode *)malloc(sizeof(struct ASTNode));
	if (node == NULL)
		return (NULL);
	node->type = ROOT;
	node->data = data;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	return (node);
}

char	**create_args_new(char **original_args, struct ArgSizes *arr_parametrs)
{
	size_t	old_size;
	size_t	i;
	char	**new_args;

	old_size = arr_parametrs->args_size;
	arr_parametrs->args_size *= 2;
	new_args = (char **)ft_realloc(original_args, sizeof(char *) * old_size,
			arr_parametrs->args_size* sizeof(char *));
	if (new_args == NULL)
	{
		free_args(original_args);
		return (NULL);
	}
	i = old_size;
	while (i < arr_parametrs->args_size)
	{
		new_args[i] = NULL;
		i++;
	}
	return (new_args);
}

void	free_args(char **args)
{
	size_t	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i] != NULL)
	{
		free(args[i]);
 		args[i] = NULL; 
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
	args = (char **)malloc((arr_parametrs.args_size + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	while (queue->size > 0 && queue->top->type == TOKEN_WORD)
	{
		token = pop_token(queue);
		if (arr_parametrs.args_count >= arr_parametrs.args_size)
			args = create_args_new(args, &arr_parametrs);
		args[arr_parametrs.args_count] = strdup(token->value.word);
		if (args[arr_parametrs.args_count] == NULL)
		{
			free_args(args);
			return (NULL);
		}
		arr_parametrs.args_count++;
		free_token(token);
	}
	args[arr_parametrs.args_count] = NULL;
	return (args);
}
