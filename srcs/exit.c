/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/05 20:11:15 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_shelldata *data)
{
	if (data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error in free_data, data is (null)\n");
		return ;
	}
	free_history(data);
	env_free(data->env);
	free_termcap(data->termcap);
	free(data);
}

void	exit_program(t_shelldata *data)
{
	write(STDOUT_FILENO, "\n", 1);
	free_data(data);
	exit(0);
}
