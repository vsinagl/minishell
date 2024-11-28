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
    // printf("sig quit, code: %i, g_sig.pid: %i\n", code, g_sig.pid); // debugging
    // print_prompt(code);
    if (g_sig_n == 0)  // At shell prompt
    {
        write(1, "\n", 1);
        print_prompt(code);
        // g_sig_n = code;
    }
    // else
    // {
    //     print_prompt(code);
    // }
}

void    sig_quit(int code)
{
    (void)code;
    if (g_sig_n == 0) // shell prompt
        return ;
    else
        ft_fprintf(STDERR_FILENO, "Quit: (core dumped)\n");
}

void    sig_init(void)
{
    g_sig_n = 0;
}

/*
function that setups specific handling for sig_int and sig_quit signals
it also set up terminal to not echo control characters, this is done
using struct termios term structure and c.lfglag flag;
*/
void	setup_signal_handling(void)
{
    signal(SIGINT, sig_int);
    signal(SIGQUIT, sig_quit);
}