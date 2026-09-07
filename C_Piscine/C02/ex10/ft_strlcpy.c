/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (src[res])
		res++;
	if (size < 1)
		return (res);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (res);
}

//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//int main() {
//	// Test 1: Normal case
//	char dest1[10];
//	assert(ft_strlcpy(dest1, "Hello",
//	sizeof(dest1)) == 5 && strcmp(dest1, "Hello") == 0);
//
//	// Test 2: Size is zero
//	char dest2[10];
//	assert(ft_strlcpy(dest2, "Hello", 1) == 5 && dest2[0] == '\0');
//
//	// Test 3: Size is less than the length of the source string
//	char dest3[10];
//	assert(ft_strlcpy(dest3, "Hello, World!",
//	sizeof(dest3)) == 13 && strcmp(dest3, "Hello, Wo") == 0);
//
//	// Test 4: Source string is empty
//	char dest4[10];
//	assert(ft_strlcpy(dest4, "", sizeof(dest4)) == 0 && dest4[0] == '\0');
//	printf("All tests passed!\n");
//	return 0;
//}