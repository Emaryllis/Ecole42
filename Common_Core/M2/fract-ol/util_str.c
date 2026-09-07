/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	while (n-- && (*s1 || *s2))
		if (*s1++ != *s2++)
			return ((unsigned char)s1[-1] - (unsigned char)s2[-1]);
	return (0);
}

void	ft_putstr_fd(const char *s, const int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

// a to double (stdlib.h)
double	ft_atodbl(const char *s)
{
	long	num;
	double	frac;
	double	pow;
	int		sign;

	num = 0;
	frac = 0;
	sign = +1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	while (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -sign;
	while (*s != '.' && *s)
		num = num * 10 + (*s++ - 48);
	if ('.' == *s)
		s++;
	while (*s)
	{
		pow /= 10;
		frac = frac + (*s++ - 48) * pow;
	}
	return ((num + frac) * sign);
}
