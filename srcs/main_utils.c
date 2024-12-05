/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/28 16:01:43 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static enum e_bool	check_quotes(char *line)
{
	int	quote_char;

	quote_char = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			if (quote_char == 0)
				quote_char = *line;
			else if (quote_char == *line)
				quote_char = 0;
		}
		line++;
	}
	if (quote_char == 0)
		return (TRUE);
	return (FALSE);
}

enum e_bool	line_ok(char *line)
{
	if (check_quotes(line) == FALSE)
	{
		ft_fprintf(STDERR_FILENO, "minishell: syntax error: unclosed quotes\n");
		return (FALSE);
	}
	if (ft_strlen(line) == 0)
		return (FALSE);
	else if (ft_strlen(line) == 1 && line[0] == ' ')
		return (FALSE);
	return (TRUE);
}

int	check_verbose(t_shelldata *data)
{
	char	*env_value;

	env_value = env_getvalue(data->env, "VERBOSE");
	if (env_value == NULL)
		return (0);
	return (ft_atoi(env_value));
}

void	print_info(void)
{
	printf("********* ************** **************\n");
	printf("********* MINISHELL v0.9 **************\n");
	printf("\n");
	printf("VERSION DESCRIPTION: ");
	printf("complete minishell, bug: echo \"-\"--> segfault\n");
	printf("Uzivatel: %s\n", getenv("USER"));
	printf("SIGINT: %i, SIGQUIT: %i\n", SIGINT, SIGQUIT);
	printf("********* ************** **************\n");
}
