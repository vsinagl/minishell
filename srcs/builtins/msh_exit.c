/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/09 14:33:51 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int msh_exit(int argc, char **argv)
{
	// msh_free(); //not implemented yet, free function that will free all the allocated memory
	printf("exit: ");
	if (argc > 1)
	{
		if (ft_isdigit(argv[1][0]) == 0)
		{
			printf(argv[1]);
			printf(" numeric argument required\n");
			return (255);
		}
		else if (argc > 2)
		{
			printf("exit: too many arguments\n");
			return (1);
		}
		else
		{
			printf("\n");
			return (ft_atoi(argv[1]));
		}
	}
}