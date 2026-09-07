/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	int	len_dest;
	int	i;

	len_dest = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (dest);
}

int	total_len(int size, char **strs, char *sep)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (i < size)
	{
		total_len += ft_strlen(strs[i]);
		i++;
	}
	total_len += ft_strlen(sep) * (size - 1) + 1;
	return (total_len);
}

char	*concat_str(int size, char **strs, char *sep, char *joined_str)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_strcat(joined_str, strs[i]);
		if (i < size - 1)
			ft_strcat(joined_str, sep);
		i++;
	}
	return (joined_str);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*joined_str;

	if (size == 0)
	{
		joined_str = malloc(1);
		joined_str[0] = '\0';
		return (joined_str);
	}
	joined_str = malloc(total_len(size, strs, sep));
	joined_str[0] = '\0';
	return (concat_str(size, strs, sep, joined_str));
}

//#include <stdio.h>
//#include <assert.h>
//#include <string.h>
//int main(void)
//{
//	// Test case 1: Empty String
//	char *strs1[] = {"", "", ""};
//	char *res = ft_strjoin(3, strs1, "");
//	assert(strcmp(res, "") == 0);
//
//	// Test case 2: Single String
//	char *strs2[] = {"a", "b", "c"};
//	res = ft_strjoin(3, strs2, "");
//	assert(strcmp(res, "abc") == 0);
//
//	// Test case 3: With separator
//	char *strs3[] = {"one", "two", "three"};
//	res = ft_strjoin(3, strs3, "-");
//	assert(strcmp(res, "one-two-three") == 0);
//	printf("All tests passed.\n");
//	return 0;
//}