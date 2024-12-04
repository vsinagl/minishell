/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:40:41 by vsinagl           #+#    #+#             */
/*   Updated: 2023/10/24 19:31:23 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	base_pos(const char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != c)
	{
		i++;
	}
	return (i);
}

int	find_char(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

unsigned int	ft_atoi_base(const char *base, char *str)
{
	int				baselen;
	int				i;
	unsigned int	num;

	num = 0;
	i = 0;
	baselen = ft_strlen(base);
	while (str[i] && find_char(base, str[i]))
	{
		num = num * baselen + base_pos(base, str[i]);
		i++;
	}
	return (num);
}
