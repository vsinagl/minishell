/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/06/18 23:59:37 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int msh_exit(int argc, char **argv)
{
	msh_free(); //not implemented yet, free function that will free all the allocated memory
	print("exit: ");
	if (argc > 1)
	{
		if (ft_isdigit(argv[1][0]) == 0)
		{
			print(argv[1]);
			print(" numeric argument required\n");
			return (255);
		}
		else if (argc > 2)
		{
			print("exit: too many arguments\n");
			return (1);
		}
		else
		{
			print("\n");
			return (ft_atoi(argv[1]));
		}
	}
}