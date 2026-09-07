/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
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

	i = 2;
	while (++i < nb)
	{
		if (nb % i == 0)
			return (0);
	}
	return (1);
}

int	ft_find_next_prime(int nb)
{
	if (nb < 2)
		return (2);
	while (nb)
	{
		if (ft_is_prime(nb) == 1)
			break ;
		nb++;
	}
	return (nb);
}

//#include <assert.h>
//#include <stdio.h>
//int main() {
//	// Test case 1: Next prime after 49
//	assert(ft_find_next_prime(49) == 53);
//
//	// Test case 2: Return same number if prime
//	assert(ft_find_next_prime(2) == 2);
//
//	// Test case 4: Next prime after 0
//	assert(ft_find_next_prime(0) == 2);
//
//	// Test case 5: Negative number
//	assert(ft_find_next_prime(-1) == 2);
//
//	printf("All test cases passed\n");
//
//	return 0;
//}