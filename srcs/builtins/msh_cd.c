/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:27:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/06/28 23:17:53 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_cd(int argc, char **argv)
{
	int	err;

	if (argc <= 1)
	{
		return (1);
	}
	else if (argc > 2)
	{
		printf("cd: string not in pwd: %s\n", argv[1]);
		return (2);
	}
	err = chdir(argv[1]);
	if (err != 0)
	{
		printf("cd: no such file or directory: %s\n", argv[1]);
		return (3);
	}
	return (0);
}
/*
int main(int argc, char **argv)
{
	int	 ret;

	ret = msh_cd(argc, argv);
	msh_pwd();
	if (ret == 0)
		return (0);
	else
		return (1);
	
} */
