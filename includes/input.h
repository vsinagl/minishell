/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/28 16:01:43 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include <curses.h>
# include <term.h>

# define ARROW_UP "\033[A"
# define ARROW_DOWN "\033[B"
# define ARROW_RIGHT "\033[C"
# define ARROW_LEFT "\033[D"
# define CTRL_C 3
# define CTRL_D 4
# define ENTER 10

typedef enum e_signal
{
	S_ERROR,
	S_BREAK,
	S_CONTINUE,
}	t_signal;

enum e_bool	is_ctrl(char c);
enum e_bool	is_arrow(char *buff);
void		handle_backspace(int *i);
t_signal	handle_ctrl_c(char *buff, t_shelldata *data);
t_signal	handle_ctrl_d(char *buff, t_shelldata *data);
void		inpt_handle_quotes(char *buff, int *quote_char, int *i,
				int bytes_read);
t_signal	handle_enter(char *buff, int quote_char);
t_history	*handle_arrow(char *buff, t_shelldata *data, t_history *head,
				int *i);
int			ft_putint(int c);

#endif
