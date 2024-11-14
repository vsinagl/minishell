/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:39 by vsinagl           #+#    #+#             */
/*   Updated: 2024/06/20 10:31:09 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_echo(int argc, char **argv)
{
	int			i;
	enum e_bool	newline;

	newline = TRUE;
	i = 1;
	printf("number of argc: %i\n", argc);
	if (argc <= 1)
		return (1);
	if (ft_strncmp("-n", argv[1], 2) == 0)
	{
		newline = FALSE;
		i++;
	}
	while (i < argc)
	{
		if (((newline == TRUE && i == 1) || (newline == FALSE && i == 2))
			&& *argv[i] == '-')
			i++;
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i < argc - 1)
			write(1, " ", 1);
		i++;
	}
	if (newline == TRUE)
		write(1, "\n", 1);
	return (0);
}
