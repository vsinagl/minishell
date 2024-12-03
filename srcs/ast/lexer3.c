/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:46:31 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 14:05:17 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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
