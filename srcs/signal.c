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


/*
@brief: Signal handler for minishell signals
CTRL+C - SIGINT
	- when we are not executing command (g_command_executing) is equal to 0, we
just print the newline, otherwise, we leave to handle ctr-c by
command(sleep for example) to handle it by itself
*/
void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
	}
	if (signo == SIGQUIT)
	{
		if (g_command_executing == 1)
		{
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		}
		else
		{
			write(STDOUT_FILENO, "\n", 1);
			write(STDOUT_FILENO, PROMPT_MAIN, ft_strlen(PROMPT_MAIN));
		}
	}
}

/**
 * @brief Sets up signal handling for the minishell.
 *
 * This function configures the necessary signal handlers to ensure that
 * the minishell application can handle various signals appropriately.
 * It is typically called during the initialization phase of the application.
 */
void	setup_signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}