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



enum e_bool	is_char_operator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == ';')
		return (TRUE);
	return (FALSE);
}

enum e_bool is_string_operator(char *str)
{
	if (str == NULL)
		return (FALSE);
	if (ft_strlen(str) == 1 && is_char_operator(str[0]))
		return (TRUE);
	else if (ft_strlen(str) == 2)
	{
		if (ft_strncmp(str, "&&", 2) == 0 || ft_strncmp(str, "||", 2) == 0)
			return (TRUE);
	}
	return (FALSE);
}