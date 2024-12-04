/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:50:06 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/05 12:34:26 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isdigit(char str);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
long			ft_atoi(const char *instr);
unsigned int	ft_atoi_base(const char *base, char *str);
int				ft_isascii(int ch);
int				ft_isprint(char c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_memcmp(const void *str1, const void *str2, size_t n);
void			*ft_memset(void *p_m, int byte, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *str, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_calloc(size_t nitems, size_t size);
void			ft_putnbr_fd(int n, int fd);
void			ft_bzero(void *p, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strnstr(const char *src, const char *find, size_t n);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			**ft_split(char const *s, char c);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char			*ft_strcat(char *dst, const char *src);
/*
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *newl);
void			ft_lstadd_back(t_list **lst, t_list *newl);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
int				ft_lstsize(t_list *lst);
*/
#endif
