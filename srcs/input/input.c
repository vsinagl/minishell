/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
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


int ft_putint(int c)
{
    return (write(STDOUT_FILENO, &c, 1));
}

static t_signal process_char(char *buff, int *i, int *quote_char, 
                        t_shelldata *data, t_history **h_head, int bytes_read)
{

    if (is_arrow(&buff[*i]))
        *h_head = handle_arrow(buff, data, *h_head, i);
    else if (buff[*i] == 127)
        handle_backspace(i);
    else if (buff[*i] == ENTER)
        return (handle_enter(buff, *quote_char));
    else if (buff[*i] == CTRL_C)
        return (handle_ctrl_c(buff, data));
    else if (buff[*i] == CTRL_D)
        return (handle_ctrl_d(buff, data));
    else if (is_ctrl(buff[*i]))
        ft_bzero(&buff[*i], BUFSIZ - *i);
    else if (buff[*i] >= 9 && buff[*i] <= 13)
        return (S_CONTINUE);
    else
        *i += write(STDOUT_FILENO, &buff[*i], bytes_read);
    return (S_CONTINUE);
}

char *process_input(t_shelldata *data)
{
    char        buff[BUFSIZ];
    int         i;
    int         bytes_read;
    int         quote_char;
    t_history   *h_head;
    t_signal    result;
    char        *line;

    i = 0;
    quote_char = 0;
    h_head = data->history;
    ft_bzero(buff, BUFSIZ);
    while (i < BUFSIZ - 1)
    {
        bytes_read = read(STDIN_FILENO, &buff[i], BUFSIZ - i);
        result = process_char(buff, &i, &quote_char, data, &h_head, bytes_read);
        if (result == S_ERROR || result == S_BREAK)
            break;
    }
    if (result == S_ERROR)
        return (NULL);
    buff[i] = '\0';
    line = ft_strdup(buff);
    ft_bzero(buff, BUFSIZ);
    return (line);
}

char *get_input(t_shelldata *data)
{
    char    *line;

	msh_set_term(&(data->termcap->new_term));
    print_prompt(data->last_status);
	line = process_input(data);
	write(STDOUT_FILENO, "\n", 1);
	msh_set_term(&(data->termcap->old_term));
    return (line);
}