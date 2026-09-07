/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int	i;

	if (nb <= 1)
		return (0);
	i = 2;
	while (i < nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

//#include <stdio.h>
//#include <assert.h>
//int main(void) {
//
//	// Test case 1: First prime number
//	assert(ft_is_prime(2) == 1);
//
//	// Test case 2: Max int prime number
//	assert(ft_is_prime(2147483647) == 1);
//
//	//Test case 3 & 4: Edge cases
//	assert(ft_is_prime(0) == 1);
//	assert(ft_is_prime(1) == 1);
//
//	// Test case 5: Negative numbers
//	assert(ft_is_prime(-1) == 1);
//
//	printf("All test cases passed\n");
//	return 0;
//}