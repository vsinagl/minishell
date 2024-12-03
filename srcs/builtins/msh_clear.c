/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:39:50 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 12:40:06 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_clear(int argc)
{
	if (!(argc < 2))
	{
		ft_fprintf(STDERR_FILENO, "msh: clear: too many arguments\n");
		return (1);
	}
	printf("\033[H\033[J");
	return (0);
}
