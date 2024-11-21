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

int options_fd(const char *input, va_list args, int fd)
{
    if (*input == 'c')
        return (ftf_putchar_fd(va_arg(args, int), fd));
    if (*input == 's')
        return (ftf_putstr_fd(va_arg(args, char *), fd));
    else if (*input == 'p')
        return (ft_pointeradr_fd(va_arg(args, void *), fd));
    else if (*input == 'd')
        return (ftf_putnbr_fd(va_arg(args, int), fd));
    else if (*input == 'i')
        return (ftf_putnbr_fd(va_arg(args, int), fd));
    else if (*input == 'u')
        return (ft_putnbr_u_fd(va_arg(args, unsigned int), fd));
    else if (*input == 'x')
        return (ft_puthex_fd(va_arg(args, unsigned int), 0, fd));
    else if (*input == 'X')
        return (ft_puthex_fd(va_arg(args, unsigned long int), 1, fd));
    else if (*input == '%')
        return (ftf_putchar_fd('%', fd));
    return (0);
}

int ft_fprintf(int fd, const char *input, ...)
{
    va_list args;
    int     count;

    count = 0;
    va_start(args, input);
    while (*input != '\0')
    {
        if (*input == '%')
            count += options_fd(++input, args, fd);
        else
        {
            write(fd, &(*input), 1);
            count++;
        }
        input++;
    }
    va_end(args);
    return (count);
}
