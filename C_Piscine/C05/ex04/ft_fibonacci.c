/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_fibonacci(int index)
{
	if (index < 0)
		return (-1);
	if (index < 2)
		return (index);
	return (ft_fibonacci(index - 2) + ft_fibonacci(index - 1));
}

//#include <assert.h>
//#include <stdio.h>
//int main() {
//	// Test case 1: Fibonacci of 0
//	assert(ft_fibonacci(0) == 0);
//
//	// Test case 2: Fibonacci of 2
//	assert(ft_fibonacci(2) == 1);
//
//	// Test case 3: Fibonacci of 3
//	assert(ft_fibonacci(3) == 2);
//
//	// Test case 4: Fibonacci of -1
//	assert(ft_fibonacci(-1) == -1);
//
//	ft_fibonacci(2147483647);
//
//	printf("All test cases passed\n");
//	return 0;
//}
