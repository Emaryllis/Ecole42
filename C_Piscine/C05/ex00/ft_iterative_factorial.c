/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	unsigned int	result;

	result = 1;
	if (nb < 0)
		return (0);
	else if (nb == 0)
		return (1);
	while (nb > 0)
	{
		result *= nb;
		nb--;
	}
	return (result);
}

//#include <assert.h>
//#include <stdio.h>
//int main() {
//	// Test case 1: Factorial of 0
//	assert(ft_iterative_factorial(0) == 1);
//
//	// Test case 2: Factorial of 1
//	assert(ft_iterative_factorial(1) == 1);
//
//	// Test case 3: Factorial of 5
//	assert(ft_iterative_factorial(5) == 120);
//
//	// Test case 4: Factorial of 10
//	assert(ft_iterative_factorial(10) == 3628800);
//
//	printf("All test cases passed\n");
//	return 0;
//}