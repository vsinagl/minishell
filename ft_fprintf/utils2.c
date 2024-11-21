/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:43:01 by vsinagl           #+#    #+#             */
/*   Updated: 2023/12/02 20:41:08 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int ft_puthex_p_fd(unsigned long int num, int fd)
{
    char    *lower;
    int     count;

    lower = "0123456789abcdef";
    count = 0;
    if (num > 15)
        count += ft_puthex_p_fd(num / 16, fd);
    count += ftf_putchar_fd(lower[num % 16], fd);
    return (count);
}

int ft_pointeradr_fd(void *ptr, int fd)
{
    int                 count;
    unsigned long int   adr;

    count = 0;
    adr = 0;
    if (ptr == NULL)
        count += ftf_putstr_fd("(nil)", fd);
    else
    {
        adr = (unsigned long int)ptr;
        count += ftf_putstr_fd("0x", fd);
        count += ft_puthex_p_fd(adr, fd);
    }
    return (count);
}
