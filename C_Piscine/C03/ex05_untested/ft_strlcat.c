/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	int	len_dest;
	int	len_src;
	int	size_final;
	int	index;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	size_final = size - len_dest - 1;
	index = 0;
	if (size_final != 0)
	{
		while (src[index] != '\0' && index < size_final)
		{
			dest[len_dest + index] = src[index];
			index++;
		}
		dest[len_dest + index] = '\0';
	}
	return (len_dest + len_src);
}

//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
//int main(void) {
//	char dest[20];
//	const char *src = "World!";
//	unsigned int size;
//
//	// Test 1: Basic concatenation
//	strcpy(dest, "Hello, ");
//	size = 14;
//	assert(ft_strlcat(dest, src, size) == 14);
//	assert(strcmp(dest, "Hello, World!") == 0);
//
//	// Test 2: Destination buffer is full
//	strcpy(dest, "Hello, ");
//	size = 8;
//	assert(ft_strlcat(dest, src, size) == 14); // "Hello, "
//	assert(strcmp(dest, "Hello, ") == 0);
//
//	// Test 3: Source string is empty
//	strcpy(dest, "Hello, ");
//	src = "";
//	size = sizeof(dest);
//	assert(ft_strlcat(dest, src, size) == 8); // "Hello, "
//	assert(strcmp(dest, "Hello, ") == 0);
//
//	// Test 4: Destination buffer is empty
//	dest[0] = '\0';
//	src = "World!";
//	size = sizeof(dest);
//	assert(ft_strlcat(dest, src, size) == 7); // "World!"
//	assert(strcmp(dest, "World!") == 0);
//
//	// Test 5: Size is 0
//	strcpy(dest, "Hello, ");
//	size = 0;
//	assert(ft_strlcat(dest, src, size) == 14); // "Hello, "
//	assert(strcmp(dest, "Hello, ") == 0);
//
//	// Test 6: Size is smaller than the length of dest
//	strcpy(dest, "Hello, ");
//	size = 7;
//	assert(ft_strlcat(dest, src, size) == 14); // "Hello, "
//	assert(strcmp(dest, "Hello, ") == 0);
//	printf("All tests passed.\n");
//	return (0);
//}