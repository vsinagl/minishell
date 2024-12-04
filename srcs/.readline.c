/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:27:15 by mmarek            #+#    #+#             */
/*   Updated: 2024/11/04 16:00:38 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
DEPRICATED FILE, I DON'T USE IT ANYMORE
handling input and reading line  with custom buffer
*/

/*
function that checks if line is complete or not
*/
static int	check_quotes(const char *line)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if ((line[i] == '"' || line[i] == '\'') && (!quote || quote == line[i]))
		{
			if (quote == line[i])
				quote = 0;
			else
				quote = line[i];
		}
	}
	return (quote);
}

static enum e_linestatus	is_line_incomplete(const char *line)
{
	int		i;
	char	quote;

	if (!line || !*line)
		return (LINE_COMPLETE);
	quote = check_quotes(line);
	if (quote)
		return (LINE_INCOMPLETE_QUOTE);
	i = 0;
	while (line[i])
		i++;
	while (--i >= 0 && (line[i] == ' ' || line[i] == '\t'))
		;
	if (i < 0)
		return (LINE_COMPLETE);
	if (line[i] == '|')
		return (LINE_INCOMPLETE_PIPE);
	if (line[i] == '\\')
		return (LINE_INCOMPLETE_BACKSLASH);
	return (LINE_COMPLETE);
}

// Modified get_complete_line function using the new checker
char	*get_complete_line(int exit_status)
{
	t_gcl_data	fdata;

	fdata.result = get_next_line(STDOUT_FILENO);
	while (fdata.result
		&& (fdata.status = is_line_incomplete(fdata.result)) != LINE_COMPLETE)
	{
		print_prompt(exit_status);
		fdata.tmp = get_next_line(STDOUT_FILENO);
		if (!fdata.tmp)
			break ;
		fdata.line = fdata.result;
		if (fdata.status == LINE_INCOMPLETE_BACKSLASH)
		{
			fdata.line[ft_strlen(fdata.line) - 1] = '\0';
			fdata.result = ft_strjoin(fdata.line, fdata.tmp);
		}
		else
			fdata.result = ft_strjoin(ft_strjoin(fdata.line, "\n"), fdata.tmp);
		free(fdata.line);
		free(fdata.tmp);
		if (!fdata.result)
			break ;
	}
	return (fdata.result);
}
