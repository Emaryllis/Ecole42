/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

int	*ft_range(int min, int max)
{
	int	*arr;
	int	i;

	if (min >= max)
		return (0);
	i = 0;
	arr = (int *)malloc(sizeof(int) * (max - min));
	while (i < max - min)
	{
		arr[i] = min + i;
		i++;
	}
	return (arr);
}

//#include <assert.h>
//#include <stdlib.h>
//void range_test(int min, int max) {
//	int *range = ft_range(min, max);
//	// Test that the function returns a non-null pointer
//	assert(range != NULL);
//	// Test that the function correctly generates the range
//	for (int i = min; i < max; i++) {
//		assert(range[i - min] == i);
//	}
//	// Test that the function returns NULL for invalid ranges
//	assert(ft_range(max, min) == NULL);
//	free(range);
//}
//int main(void) {
//	int min = 0;
//	int max = 5;
//
//	return 0;
//}