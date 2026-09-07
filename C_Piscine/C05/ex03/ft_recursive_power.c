/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, (power - 1)));
}

//#include <assert.h>
//#include <stdio.h>
//int main() {
//	// Test case 1: Power of 0
//	assert(ft_recursive_power(2, 0) == 1);
//
//	// Test case 2: Power of 1
//	assert(ft_recursive_power(2, 1) == 2);
//
//	// Test case 3: Power of 2
//	assert(ft_recursive_power(2, 2) == 4);
//
//	// Test case 4: Number of 0
//	assert(ft_recursive_power(0, 3) == 0);
//
//	// Test case 4: Number of -2
//	assert(ft_recursive_power(-2, 3) == -8);
//
//	printf("All test cases passed\n");
//	return 0;
//}