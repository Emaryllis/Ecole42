/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	check_base(char *str)
{
	int	i;
	int	z;

	i = 0;
	if (str[0] == '\0' || str[1] == '\0')
		return (0);
	while (str[i])
	{
		z = i + 1;
		if (str[i] == '+' || str[i] == '-')
			return (0);
		if (str[i] < 32 || str[i] > 126)
			return (0);
		while (str[z])
		{
			if (str[i] == str[z])
				return (0);
			z++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *str)
{
	int	size_base;
	int	nbr_final[100];
	int	i;

	i = 0;
	size_base = 0;
	if (check_base(str))
	{
		if (nbr < 0)
		{
			nbr = -nbr;
			write(1, "-", 1);
		}
		while (str[size_base])
			size_base++;
		while (nbr)
		{
			nbr_final[i] = nbr % size_base;
			nbr = nbr / size_base;
			i++;
		}
		while (--i >= 0)
			write(1, &str[nbr_final[i]], 1);
	}
}

//#include <stdio.h>
//int main() {
//
//	// Test with decimal base
//	ft_putnbr_base(10, "0123456789"); // 10
//	printf("\n");
//
//	// Test with binary base
//	ft_putnbr_base(10, "01"); // 1010
//	printf("\n");
//
//	// Test with hexadecimal base
//	ft_putnbr_base(15, "0123456789ABCDEF"); // F
//	printf("\n");
//
//	// Test with octal base
//	ft_putnbr_base(8, "poneyvif"); // op
//	printf("\n");
//
//	// Test with negative number
//	ft_putnbr_base(-10, "0123456789"); // -10
//	printf("\n");
//
//	// Test with invalid base: empty base
//	ft_putnbr_base(10, "");
//	printf("\n");
//
//	// Test with invalid base: base of size 1
//	ft_putnbr_base(10, "0");
//	printf("\n");
//
//	// Test with invalid base: base contains same character twice
//	ft_putnbr_base(10, "01234567890");
//	printf("\n");
//
//	// Test with invalid base: base contains '+' or '-'
//	ft_putnbr_base(10, "0123456789+-");
//	return 0;
//}