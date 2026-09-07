/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:08:29 by egoh              #+#    #+#             */
/*   Updated: 2025/09/11 15:08:29 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBC_H
# define LIBC_H
# include <stddef.h>

void	*ft_calloc(size_t amt, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_min(int a, int b);
int		ft_printf(const char *format, ...);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
int		ft_sqrt(int nb);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
#endif
