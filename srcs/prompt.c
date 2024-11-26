/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/22 09:01:21 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(int exit_status)
{
	char *user;

	user = getenv("USER");
	printf("%smsh:%s ", PROMPT_USER, user);
	if (exit_status == 0)
	{
		printf(PROMPT_OK);
		printf(PROMPT);
		printf(PROMPT_RESET);

	}
	else
	{
		printf(PROMPT_ERROR);
		printf(PROMPT);
		printf(PROMPT_RESET);
	}
	fflush(stdout);
}

// char *readline_prompt(int exit_status)
// {
// 	char *line;

// 	line = readline("");
// 	return (line);
// }