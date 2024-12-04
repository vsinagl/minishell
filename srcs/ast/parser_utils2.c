/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/04 16:01:43 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
function that pops first element (the first added element) from stack
*/
t_token	*pop_token(t_tokenqueue *tokens)
{
	t_token	*token;

	if (tokens->size == 0 || tokens->top == NULL)
		return (NULL);
	token = tokens->top;
	tokens->top = tokens->top->next;
	tokens->size--;
	return (token);
}

void	free_token(t_token *token)
{
	if (token->type == TOKEN_WORD)
	{
		if (token->u_value.word != NULL)
			free(token->u_value.word);
	}
	free(token);
}

void	free_token_queue(t_tokenqueue *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens->top;
	while (current != NULL)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
	free(tokens);
}
