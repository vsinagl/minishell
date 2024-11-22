/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:27:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/22 13:48:49 by vsinagl          ###   ########.fr       */
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

int	msh_export(int argc, char **argv, t_env *head) 
{
	int		border;
	char	*str1;
	char	*str2;
	int		i;
	
	if (head == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error in msh_export, t_env head is (null)");
		return 1;
	}
	if (argc < 1)
		return 1;
	else if (argc == 1)
		msh_env(head);
	else
	{
		i = 1;
		while (i < argc)
		{
			border = ft_str_findchar(argv[i], '=');
			if (border == 0)
				return 2;
			str1 = ft_substr(argv[i], 0, (size_t)(border));
			str2 = ft_strdup(ft_strchr(argv[i], '=') + 1);
			t_env *header = env_add(head, str1, str2);
			i++;
		}
	}
	return (0);
}
