/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	i;
	int	diff;
	int	*result;

	if (min >= max)
	{
		*range = 0;
		return (0);
	}
	i = 0;
	diff = max - min;
	result = malloc(sizeof(int) * diff);
	if (result == 0)
	{
		*range = 0;
		return (-1);
	}
	*range = result;
	while (i < diff)
	{
		result[i] = min + i;
		i++;
	}
	return (i);
}

//#include <assert.h>
//#include <stdio.h>
//int* test_range(int min, int max, int expected_range_size) {
//	int *range = NULL;
//	int range_size = ft_ultimate_range(&range, min, max);
//	assert(range_size == expected_range_size);
//	return range;
//}
//int main() {
//	// Test case 1: Normal range
//	int *range1 = test_range(0, 5, 5);
//	for (int i = 0; i < 5; i++) assert(range1[i] == i);
//	free(range1);
//	printf("Test case 1 passed!\n");
//
//	// Test case 2: Single element range
//	int *range2 = test_range(10, 11, 1);
//	assert(range2[0] == 10);
//	free(range2);
//	printf("Test case 2 passed!\n");
//
//	// Test case 3: Max int range
//	int *range4 = test_range(0, 2147483647, 2147483647);
//	free(range4);
//	printf("Test case 3 passed!\n");
//
//	// Test case 4: Invalid range (min >= max)
//	int *range3 = test_range(20, 15, 0);
//	assert(range3 == NULL);
//	printf("Test case 4 passed!\n");
//	return 0;
//}