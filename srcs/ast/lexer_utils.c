/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/04 16:01:40 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	print_token(struct Token *token)
{
	if (token->type == TOKEN_WORD)
		printf("Word: %s\n", token->value.word);
	else
		printf("Operator: %d\n", token->value.op);
}

// helper function --> print all tokens in TokenStack !
void	print_tokens(struct TokenQueue *tokens)
{
	struct Token	*current;

	current = tokens->top;
	while (current != NULL)
	{
		print_token(current);
		current = current->next;
	}
}
