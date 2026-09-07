/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

char	*ft_strdup(char *str)
{
	int		i;
	char	*copy;

	i = 0;
	while (str[i])
		i++;
	copy = (char *)malloc(i + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

//#include <assert.h>
//#include <string.h>
//int main() {
//	char *original = "Hello, World!";
//	char *copy = ft_strdup(original);
//
//	// Test if the copy is not NULL
//	assert(copy != NULL);
//
//	// Test if the copy is equal to the original
//	assert(strcmp(original, copy) == 0);
//
//	// Test if the copy and original are not the same memory location
//	assert(copy != original);
//
//	free(copy);
//	printf("All tests passed!\n");
//	return 0;
//}