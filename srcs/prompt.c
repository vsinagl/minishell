/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/22 09:01:21 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(int exit_status)
{
	ft_putstr_fd(PROMPT_USER, STDOUT_FILENO);
	ft_putstr_fd("msh:", STDOUT_FILENO);
	if (exit_status == 0)
	{
		ft_putstr_fd(PROMPT_OK, STDOUT_FILENO);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		ft_putstr_fd(PROMPT_RESET, STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(PROMPT_ERROR, STDOUT_FILENO);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		ft_putstr_fd(PROMPT_RESET, STDOUT_FILENO);
	}
}
