/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/08/31 17:17:31 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
- helper function that returns the legnth of array of arrays of characters
- add this function to libft
TODO: dont forgot to put libft to github!
*/
int	ft_strarr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

/*
helper function, print array of strings. In Code,
	mainly used for printing node arguments
*/
void	print_args2(char **args)
{
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		printf("%s ", args[i]);
		i++;
	}
}
