/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	if_valid(int table[10], int x, int y)
{
	int	i;

	i = -1;
	while (++i < x)
		if (y == table[i] || i + table[i] == x + y || i - table[i] == x - y)
			return (0);
	return (1);
}

void	solver(int table[10], int *res, int pos)
{
	int	i;
	int	i2;

	if (pos == 10)
	{
		*res += 1;
		i2 = -1;
		while (++i2 < 10)
			ft_putchar(table[i2] + '0');
		ft_putchar('\n');
	}
	else
	{
		i = -1;
		while (++i < 10)
		{
			if (if_valid(table, pos, i))
			{
				table[pos] = i;
				solver(table, res, pos + 1);
			}
		}
	}
}

int	ft_ten_queens_puzzle(void)
{
	int		table[10];
	int		i;
	int		res;

	i = -1;
	while (++i < 10)
		table[i] = -1;
	res = 0;
	solver(table, &res, 0);
	return (res);
}

//#include <stdio.h>
//int	main(void)
//{
//	ft_ten_queens_puzzle();
//	return (0);
//}