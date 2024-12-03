/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 13:39:38 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/input.h"
#include "../../includes/minishell.h"
#include <curses.h>
#include <term.h>

int	ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

static t_signal	process_char(char *buff, int *i, t_shelldata *data,
		t_input input)
{
	if (is_arrow(&buff[*i]))
		*(input.h_head) = handle_arrow(buff, data, *(input.h_head), i);
	else if (buff[*i] == 127)
		handle_backspace(i);
	else if (buff[*i] == ENTER)
		return (handle_enter(buff, 0));
	else if (buff[*i] == CTRL_C)
		return (handle_ctrl_c(buff, data));
	else if (buff[*i] == CTRL_D)
		return (handle_ctrl_d(buff, data));
	else if (is_ctrl(buff[*i]))
		ft_bzero(&buff[*i], BUFSIZ - *i);
	else if (buff[*i] >= 9 && buff[*i] <= 13)
		return (S_CONTINUE);
	else
		*i += write(STDOUT_FILENO, &buff[*i], input.bytes_read);
	return (S_CONTINUE);
}

char	*process_input(t_shelldata *data)
{
	char	buff[BUFSIZ];
	int		i;
	t_input	input;
	char	*line;

	i = 0;
	input.h_head = &data->history;
	ft_bzero(buff, BUFSIZ);
	while (i < BUFSIZ - 1)
	{
		input.bytes_read = read(STDIN_FILENO, &buff[i], BUFSIZ - i);
		input.result = process_char(buff, &i, data, input);
		if (input.result == S_ERROR || input.result == S_BREAK)
			break ;
	}
	if (input.result == S_ERROR)
		return (NULL);
	buff[i] = '\0';
	line = ft_strdup(buff);
	ft_bzero(buff, BUFSIZ);
	return (line);
}

char	*get_input(t_shelldata *data)
{
	char	*line;

	msh_set_term(&(data->termcap->new_term));
	print_prompt(data->last_status);
	line = process_input(data);
	write(STDOUT_FILENO, "\n", 1);
	msh_set_term(&(data->termcap->old_term));
	return (line);
}
