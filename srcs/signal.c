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

/*
process ending signal that prints output on terminal based on received signal from 
command. 
*/
// int process_pending_signal(int is_executing)
// {
//     printf("g_received_signal: %d\n, is_executing: %i\n", g_received_signal, is_executing); // debugging
//     if (g_received_signal == 0)
//         return (0);
//     else if (g_received_signal == SIGINT)
//     {
//         write(STDOUT_FILENO, "\n> ", 1);
//         g_received_signal = 0;
// 		return (0);
//     }
//     else if (g_received_signal == SIGQUIT)
//     {
//         if (is_executing)
//             write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
//         // else
//         // {
//         //     write(STDOUT_FILENO, "\n", 1);
//         //     write(STDOUT_FILENO, PROMPT_MAIN, ft_strlen(PROMPT_MAIN));
//         // }
//         g_received_signal = 0;
//         return (0);
//     }
//     return (0);
// }


/*
@brief: Signal handler for minishell signals
CTRL+C - SIGINT
*/
// void    signal_handler2(int signo)
// {
//     g_received_signal = signo;
// }

/**
 * @brief Sets up signal handling for the minishell.
 *
 * This function configures the necessary signal handlers to ensure that
 * the minishell application can handle various signals appropriately.
 * It is typically called during the initialization phase of the application.
 */
// void	setup_signal_handling(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = signal_handler2;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }

//TEST !!!



void    sig_int()
{
    // printf("sig quit, code: %i, g_sig.pid: %i\n", code, g_sig.pid); // debugging
    if (g_sig.pid == 0)  // At shell prompt
    {
        printf("\b\b  ");
		printf("\n%s", PROMPT_MAIN);
    }
    else
        ft_putstr_fd("\n", STDERR_FILENO);
}

void    sig_quit()
{
    // printf("sig quit, code: %i, g_sig.pid: %i\n", code, g_sig.pid); // debugging
    if (g_sig.pid == 0)  // Only handle during command execution
    {
        // printf("\033[E");
        // printf("\033[A");
        return ;
    }
    else
        ft_fprintf(STDERR_FILENO, "Quit: (core dumped)\n");
}

void    sig_init(void)
{
    g_sig.pid = 0;
    g_sig.exit_status = 0;
}

void signal_handler(int code)
{
    if (code == SIGINT)
        sig_int();
    else if (code == SIGQUIT)
        sig_quit();
}

/*
function that setups specific handling for sig_int and sig_quit signals
it also set up terminal to not echo control characters, this is done
using struct termios term;
*/
void	setup_signal_handling(void)
{
    // Remove sigaction struct and use signal() directly
    signal(SIGINT, sig_int);
    signal(SIGQUIT, sig_quit);
    
    // Set up terminal to not echo control characters
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
/*
void    setup_signal_handling(void)
{
    struct sigaction    sa;

    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_int;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = sig_quit;
    sigaction(SIGQUIT, &sa, NULL);
    
    rl_catch_signals = 0;
}
*/