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

static int	check_quotes(const char *line, size_t *i, char *quote_char)
{
	if ((line[*i] == '"' || line[*i] == '\''))
	{
		if (*quote_char == 0)
		{
			*quote_char = line[*i];
			return (1);
		}
		else if (line[*i] == *quote_char)
		{
			*quote_char = 0;
			return (1);
		}
	}
	return (0);
}

/*
Helper function to get the position of the last meaningful character in a line.
*/
static size_t	get_last_meaningful_char(const char *line)
{
	size_t	i;

	i = ft_strlen(line);
	while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t' || line[i
			- 1] == '\n'))
		i--;
	return (i);
}

/*
function that checks if line is complete or not
*/
static enum e_linestatus is_line_incomplete(const char *line)
{
    int     i;
    char    quote;
    size_t  len;

    if (!line || !*line)
        return (LINE_COMPLETE);
    i = -1;
    quote = 0;
    while (line[++i])
    {
        if ((line[i] == '"' || line[i] == '\'') && 
            (!quote || quote == line[i]))
            quote = (quote == line[i]) ? 0 : line[i];
    }
    if (quote)
        return (LINE_INCOMPLETE_QUOTE);
    len = i;
    while (--i >= 0 && (line[i] == ' ' || line[i] == '\t'))
        ;
    if (i < 0)
        return (LINE_COMPLETE);
    return (line[i] == '|' ? LINE_INCOMPLETE_PIPE : 
            line[i] == '\\' ? LINE_INCOMPLETE_BACKSLASH : 
            LINE_COMPLETE);
}


// Modified get_complete_line function using the new checker
char	*get_complete_line(void)
{
	t_gcl_data	fdata;

	fdata.result = readline(PROMPT_MAIN);
	while (fdata.result
		&& (fdata.status = is_line_incomplete(fdata.result)) != LINE_COMPLETE)
	{
		fdata.tmp = readline(PROMPT_CONTINUE);
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
	return fdata.result;
}