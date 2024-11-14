/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:27:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/06/28 23:17:53 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_str_findchar(const char *str, char to_find)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_find)
			return (i);
		i++;
	}
	return 0;
}

int	msh_export(int argc, char **argv, t_env **env) 
{
	int		border;
	// char	*str1;
	// char	*str2;
	
	if (argc <= 1)
		return 1;
	border = ft_str_findchar(argv[1], '=');
	if (border == 0)
		return 2;
	// str1 = ft_substr(argv[1], 0, (size_t)(border));
	// str2 = ft_strdup(ft_strchr(argv[1], '=') + 1);
	env_add(env, ft_substr(argv[1], 0, (size_t)(border)), ft_strdup(ft_strchr(argv[1], '=') + 1));
	return (0);
}
