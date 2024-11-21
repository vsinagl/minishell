/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:43:01 by vsinagl           #+#    #+#             */
/*   Updated: 2023/12/02 20:41:08 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int ftf_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
    return (1);
}

int ftf_putstr_fd(char *s, int fd)
{
    int i;

    i = 0;
    if (s == NULL)
        s = "(null)";
    while (s[i] != '\0')
    {
        write(fd, &s[i], 1);
        i++;
    }
    return (i);
}

int ftf_putnbr_fd(int num, int fd)
{
    int count;
    int mod;

    count = 0;
    if (num < 0)
    {
        count += ftf_putchar_fd('-', fd);
        if (num == INT_MIN)
        {
            count += ftf_putstr_fd("2147483648", fd);
            return (count);
        }
        num = num * (-1);
    }
    mod = num % 10;
    if (num / 10 > 0)
        count += ftf_putnbr_fd(num / 10, fd);
    count += ftf_putchar_fd(mod + '0', fd);
    return (count);
}

int ft_putnbr_u_fd(unsigned int num, int fd)
{
    int count;
    int mod;

    count = 0;
    mod = num % 10;
    if (num / 10 > 0)
        count += ft_putnbr_u_fd(num / 10, fd);
    count += ftf_putchar_fd(mod + '0', fd);
    return (count);
}

int ft_puthex_fd(unsigned int num, int option, int fd)
{
    char    *upper;
    char    *lower;
    int     count;

    upper = "0123456789ABCDEF";
    lower = "0123456789abcdef";
    count = 0;
    if (num > 15)
        count += ft_puthex_fd(num / 16, option, fd);
    if (option == 1)
        count += ftf_putchar_fd(upper[num % 16], fd);
    else
        count += ftf_putchar_fd(lower[num % 16], fd);
    return (count);
}
