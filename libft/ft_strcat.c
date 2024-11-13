/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 07:25:13 by vsinagl           #+#    #+#             */
/*   Updated: 2023/10/26 08:06:35 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Concatenates src string to dst string
*/
char	*ft_strcat(char *dst, const char *src)
{
	char	*dst_start;

	if (dst == NULL || src == NULL)
		return (NULL);
	dst_start = dst;
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (dst_start);
}
