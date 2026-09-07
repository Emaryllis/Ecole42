/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int	i;
	int	total;

	i = 1;
	total = 0;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i = -i;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		total = total * 10 + (*str - '0');
		str++;
	}
	return (total * i);
}

//#include <assert.h>
//int main() {
//	assert(ft_atoi("0") == 0);
//	assert(ft_atoi("1") == 1);
//	assert(ft_atoi("123") == 123);
//	assert(ft_atoi("-123") == -123);
//	assert(ft_atoi("   -123") == -123);
//	assert(ft_atoi("   123abc") == 123);
//	return 0;
//}
