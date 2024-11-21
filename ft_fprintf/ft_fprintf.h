/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:43:01 by vsinagl           #+#    #+#             */
/*   Updated: 2023/12/02 20:41:08 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include "../libft/libft.h"

int ftf_putchar_fd(char c, int fd);
int ftf_putstr_fd(char *s, int fd);
int ftf_putnbr_fd(int num, int fd);
int ft_putnbr_u_fd(unsigned int num, int fd);
int ft_puthex_fd(unsigned int num, int option, int fd);
int ft_pointeradr_fd(void *ptr, int fd);
int ft_fprintf(int fd, const char *input, ...);


#endif
