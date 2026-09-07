/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:10:12 by egoh              #+#    #+#             */
/*   Updated: 2024/03/19 20:10:20 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stock_str.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

void	ft_putnbr(int nb)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_putchar(n + 48);
	}
}

void	ft_show_tab(struct s_stock_str *par)
{
	int		i;

	i = -1;
	while (par[++i].str != 0)
	{
		ft_putstr(par[i].str);
		ft_putchar('\n');
		ft_putnbr(par[i].size);
		ft_putchar('\n');
		ft_putstr(par[i].copy);
		ft_putchar('\n');
	}
}

//#include <assert.h>
//#include <string.h>
//#include <stdio.h>
//#include "ft_strs_to_tab.c"
//int main() {
//	// Test case 1: Normal case
//	char *av1[] = {"Hello", "World"};
//	int ac1 = 2;
//	t_stock_str *result1 = ft_strs_to_tab(ac1, av1);
//	assert(result1 != NULL);
//	assert(strcmp(result1[0].str, "Hello") == 0); // Expect "Hello"
//	assert(strcmp(result1[0].copy, "Hello") == 0); // Expect "Hello"
//	assert(result1[0].size == 5); // Expect 5
//	assert(strcmp(result1[1].str, "World") == 0); // Expect "World"
//	assert(strcmp(result1[1].copy, "World") == 0); // Expect "World"
//	assert(result1[1].size == 5); // Expect 5
//	assert(result1[2].str == 0); // Expect NULL
//
//	// Test case 2: Empty strings
//	char *av2[] = {"", ""};
//	int ac2 = 2;
//	t_stock_str *result2 = ft_strs_to_tab(ac2, av2);
//	assert(result2 != NULL);
//	assert(strcmp(result2[0].str, "") == 0); // Expect ""
//	assert(strcmp(result2[0].copy, "") == 0); // Expect ""
//	assert(result2[0].size == 0); // Expect 0
//	assert(strcmp(result2[1].str, "") == 0); // Expect ""
//	assert(strcmp(result2[1].copy, "") == 0); // Expect ""
//	assert(result2[1].size == 0); // Expect 0
//	assert(result2[2].str == 0); // Expect NULL
//
//	// Test case 3: Single string
//	char *av3[] = {"Single"};
//	int ac3 = 1;
//	t_stock_str *result3 = ft_strs_to_tab(ac3, av3);
//	assert(result3 != NULL);
//	assert(strcmp(result3[0].str, "Single") == 0); // Expect "Single"
//	assert(strcmp(result3[0].copy, "Single") == 0); // Expect "Single"
//	assert(result3[0].size == 6); // Expect 6
//	assert(result3[1].str == 0); // Expect NULL
//	printf("All test cases passed!\n");
//	return 0;
//}