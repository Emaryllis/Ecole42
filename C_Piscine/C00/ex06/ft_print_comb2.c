/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	print(char c)
{
	write(1, &c, 1);
}

void	print_num(int n)
{
	if (n >= 10)
	{
		print_num(n / 10);
	}
	print((n % 10) + '0');
}

void	print_digits(int i, int j)
{
	if (i < 10)
	{
		print('0');
	}
	print_num(i);
	print(' ');
	if (j < 10)
	{
		print('0');
	}
	print_num(j);
	if (i < 98)
	{
		write(1, ", ", 2);
	}
}

void	ft_print_comb2(void)
{
	int	i;
	int	j;

	i = 0;
	while (i <= 99)
	{
		j = i + 1;
		while (j <= 99)
		{
			print_digits(i, j);
			j++;
		}
		i++;
	}
}
