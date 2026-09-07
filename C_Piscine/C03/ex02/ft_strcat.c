/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
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
//	assert(strcmp(ft_strcat(dest, src), "Hello world") == 0);
//
//	// Test 2: dest is empty
//	strcpy(dest, "");
//	assert(strcmp(ft_strcat(dest, src), "world") == 0);
//
//	// Test 3: src is empty
//	strcpy(dest, "Hello ");
//	strcpy(src, "");
//	assert(strcmp(ft_strcat(dest, src), "Hello ") == 0);
//
//	printf("All tests passed!\n");
//
//	return 0;
//}