/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	ft_sqrt(int nb)
{
	int	sqrt;

	if (nb < 0)
		return (0);
	sqrt = 1;
	while (sqrt * sqrt < nb && sqrt != 2147483647)
		++sqrt;
	if (sqrt * sqrt == nb)
		return (sqrt);
	return (0);
}

//#include <stdio.h>
//#include <assert.h>
//int main() {
//	// Test case 1: Square Root of 0
//	assert(ft_sqrt(0) == 0);
//
//	// Test case 2: Square Root of 2
//	assert(ft_sqrt(2) == 0);
//
//	// Test case 3: Square Root of 4
//	assert(ft_sqrt(4) == 2);
//
//	// Test case 4 : Square Root of 49
//	assert(ft_sqrt(49) == 7);
//
//	// Test case 5: Square Root of -1
//	assert(ft_sqrt(-1) == 0);
//
//	// Test case 6: Square Root of 5
//	assert(ft_sqrt(5) == 0);
//
//	// Test case 7: Int limit
//	assert(ft_sqrt(2147483647) == 0);
//
//	printf("All test cases passed\n");
//	return 0;
//}
