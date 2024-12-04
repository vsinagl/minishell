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
#include <curses.h>
#include <term.h>

/**
 * @brief Initialization functions for the minishell project.
 *
 * This function allocates memory for a t_termcap structure,
retrieves the terminal type from the environment,
and sets up the terminal attributes for non-canonical mode

* with no echo. It also retrieves the termcap strings for 
cursor movement and line deletion.

 * The initialization process includes setting terminal flags to ensure
 * proper input and output behavior. These flags control various terminal
 * attributes such as input mode, output mode, control characters, and
 * local modes. Proper configuration of these flags is crucial for the
 * correct functioning of the shell.
 *
 * @return A pointer to the initialized t_termcap structure,
	or NULL if initialization fails.
 */
t_termcap	*init_term(void)
{
	t_termcap	*termcap;
	char		*term_type;

	termcap = (t_termcap *)malloc(sizeof(t_termcap));
	term_type = getenv("TERM");
	tcgetattr(STDIN_FILENO, &termcap->old_term);
	tcgetattr(STDIN_FILENO, &termcap->new_term);
	if (tgetent(termcap->buffer, term_type) < 0)
	{
		printf("wtf\n");
		return (NULL);
	}
	termcap->new_term = termcap->old_term;
	termcap->new_term.c_lflag &= ~ISIG;
	termcap->new_term.c_lflag &= ~ICANON;
	termcap->new_term.c_lflag &= ~ECHO;
	termcap->new_term.c_cc[VMIN] = 1;
	termcap->new_term.c_cc[VTIME] = 0;
	termcap->move_s = tgetstr("cr", &termcap->buffer);
	termcap->del_l = tgetstr("dl", &termcap->buffer);
	return (termcap);
}

/*
We have two type of terminals settings, default one and our custom
one for handling minishell input. We can switch between terminal with
this function.
*/
void	msh_set_term(struct termios *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

/*
Function that initialized data at begging of the program.
*/
// int	init_data(t_shelldata *data)
// {

// 	data->history = NULL;
// 	data->env = init_env();
// 	data->last_status = 0;
// 	data->termcap = init_term();
// 	if (data->termcap == NULL)
// 		return (1);
// 	return (0);
// }

t_shelldata	*init_data()
{

	t_shelldata		*data;

	data = (t_shelldata *)malloc(sizeof(t_shelldata));
	data->history = NULL;
	data->env = init_env();
	data->last_status = 0;
	data->termcap = init_term();
	if (data->termcap == NULL)
	{
		free_data(data);
		return (NULL);
	}
	return (data);
}
