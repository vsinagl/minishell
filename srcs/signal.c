/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2024/06/12 20:25:54 by mmarek            #+#    #+#             */
/*   updated: 2024/11/04 17:41:13 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <termios.h>


void    sig_int(int code)
{
    (void)code;
    write(1, "\n", 1);
}

void    sig_quit(int code)
{
    (void)code;
    ft_fprintf(STDERR_FILENO, "Quit: (core dumped)\n");
}

// void    sig_init(void)
// {
//     g_sig_n = 0;
// }

/*
function that setups specific handling for sig_int and sig_quit signals
-sigint just do what it always do (terminate process) and quit with newline
- sigquit prints Quit: (core dumped) and terminate process
- process terminate by sigquit is alwys terminate with segmentation fault
*/
void	setup_signal_handling(void)
{
    signal(SIGINT, sig_int);
    signal(SIGQUIT, sig_quit);
}