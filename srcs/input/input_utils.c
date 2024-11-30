/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/28 16:01:43 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/input.h"
#include <term.h>
#include <curses.h>

enum e_bool is_ctrl(char c)
{
	if (c == CTRL_C || c == CTRL_D || c == ENTER)
		return FALSE;
	if ((0 <= c && c <= 31) || c == 127)
		return TRUE;
	return FALSE;
}

void handle_backspace(int *i)
{
    if (*i > 0)
    {
        write(STDOUT_FILENO, "\b \b", 3);
        (*i)--;
    }
}

t_signal	handle_ctrl_c(char *buff, t_shelldata *data)
{
    write(STDOUT_FILENO, "^C", 2);
	data->last_status = 130;
    ft_bzero(buff, BUFSIZ);
    return (S_BREAK);
}

t_signal	handle_ctrl_d(char *buff, t_shelldata *data)
{
    ft_putstr_fd("\nexit", 1);
    ft_bzero(buff, BUFSIZ);
	data->last_status = 0;
    exit_program(data);
    return (S_ERROR);
}

//!depricated, quotes are checked after we get the line (read it)
void inpt_handle_quotes(char *buff, int *quote_char, int *i, int bytes_read)
{
    if (*quote_char == 0)
        *quote_char = buff[*i];
    else if (*quote_char == buff[*i])
        *quote_char = 0;
    *i += write(STDOUT_FILENO, &buff[*i], bytes_read);
}