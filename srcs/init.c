/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:27:15 by vsinagl            #+#    #+#            */
/*   Updated: 2024/11/04 16:00:38 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <term.h>
#include <curses.h>

t_termcap *init_term()
{
	t_termcap *termcap;
	char 	*term_type;

	termcap = (t_termcap *)malloc(sizeof(t_termcap));
	term_type = getenv("TERM");
	tcgetattr(STDIN_FILENO, &termcap->old_term);
	tcgetattr(STDIN_FILENO, &termcap->new_term);


	if (tgetent(termcap->buffer, term_type) <= 0)
	{
		//some error handling here
		return NULL;
	}
	termcap->new_term = termcap->old_term;
	termcap->new_term.c_lflag &= ~ISIG;
	termcap->new_term.c_lflag &= ~ICANON;  // Disable canonical mode
	termcap->new_term.c_lflag &= ~ECHO;  // Disable printing input
	termcap->new_term.c_cc[VMIN] = 1;      // Read minimum 1 character
	termcap->new_term.c_cc[VTIME] = 0;     // No timeout

	termcap->move_s = tgetstr("cr", &termcap->buffer);
	termcap->del_l = tgetstr("dl", &termcap->buffer);
	return (termcap);
}

void	msh_set_term(struct termios *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}




void	init_data(t_shelldata *data)
{
	data->history = NULL;
	data->env = init_env();
	data->last_status = 0;
	data->termcap = init_term();
}
