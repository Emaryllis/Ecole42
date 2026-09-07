/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
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
	while (str[i])
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

//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//int main() {
//	char str[100];
//	char to_find[] = "world";
//
//	// Test 1: Normal case
//	strcpy(str, "Hello world");
//	assert(strcmp(ft_strstr(str, to_find), "world") == 0);
//
//	// Test 2: to_find is not in str
//	strcpy(str, "Hello planet");
//	assert(ft_strstr(str, to_find) == NULL);
//
//	// Test 3: str is empty
//	strcpy(str, "");
//	assert(ft_strstr(str, to_find) == NULL);
//
//	// Test 4: to_find is empty
//	strcpy(str, "Hello world");
//	strcpy(to_find, "");
//	assert(strcmp(ft_strstr(str, to_find), "Hello world") == 0);
//
//	printf("All tests passed!\n");
//
//	return 0;
//}