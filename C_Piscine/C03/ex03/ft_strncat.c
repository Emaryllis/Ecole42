/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && j < nb)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//int main() {
//	char dest[100];
//	char src[] = "world";
//
//	// Test 1: Normal case
//	strcpy(dest, "Hello ");
//	assert(strcmp(ft_strncat(dest, src, 5), "Hello world") == 0);
//
//	// Test 2: nb is zero
//	strcpy(dest, "Hello ");
//	assert(strcmp(ft_strncat(dest, src, 0), "Hello ") == 0);
//
//	// Test 3: nb is greater than length of src
//	strcpy(dest, "Hello ");
//	assert(strcmp(ft_strncat(dest, src, 10), "Hello world") == 0);
//
//	// Test 4: dest is empty
//	strcpy(dest, "");
//	assert(strcmp(ft_strncat(dest, src, 5), "world") == 0);
//
//	// Test 5: src is empty
//	strcpy(dest, "Hello ");
//	strcpy(src, "");
//	assert(strcmp(ft_strncat(dest, src, 5), "Hello ") == 0);
//
//	printf("All tests passed!\n");
//	return 0;
//}