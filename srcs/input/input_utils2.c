/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/05 20:06:50 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/input.h"
#include <curses.h>
#include <term.h>

enum e_bool	is_arrow(char *buff)
{
	if (!ft_strcmp(buff, ARROW_UP) || !ft_strcmp(buff, ARROW_DOWN))
		return (TRUE);
	return (FALSE);
}

t_history	*handle_arrow(char *buff, t_shelldata *data, t_history *head,
		int *i)
{
	char		*last_com;
	t_history	*curr;

	curr = head;
	if (!ft_strcmp((buff + *i), ARROW_DOWN))
		curr = move_head(head, 1);
	if (curr == NULL)
		return (head);
	last_com = curr->data;
	if (last_com == NULL)
		return (head);
	if (!ft_strcmp((buff + *i), ARROW_UP))
		curr = move_head(head, 0);
	tputs(data->termcap->del_l, 1, ft_putint);
	tputs(data->termcap->move_s, 1, ft_putint);
	print_prompt(0);
	ft_bzero(buff, BUFSIZ);
	ft_strlcpy(buff, last_com, BUFSIZ);
	*i = write(STDOUT_FILENO, buff, ft_strlen(buff));
	return (curr);
}

/*
	function that handle enter key press in shell
	if we are in quotes we send a (char*)1 --> this is signal
	to break the loop
*/
t_signal	handle_enter(char *buff, int quote_char)
{
	if (quote_char != 0)
	{
		ft_fprintf(STDERR_FILENO, "\nminishell: syntax error: unclosed quotes");
		ft_bzero(buff, BUFSIZ);
		return (S_BREAK);
	}
	return (S_BREAK);
}
