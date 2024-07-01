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

int	msh_pwd(void)
{
	char	buff[10000];
	char	*ptr_ret;

	ptr_ret = getcwd(buff, 10000);
	if (ptr_ret == NULL)
	{
		ft_putstr_fd("ERROR: path to long!\n", STDOUT_FILENO);
		return (1);
	}
	ft_putstr_fd(buff, STDOUT_FILENO);
	return 0;
}
