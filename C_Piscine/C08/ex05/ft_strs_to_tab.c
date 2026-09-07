/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:10:12 by egoh              #+#    #+#             */
/*   Updated: 2024/03/19 20:10:20 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include "ft_stock_str.h"

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (*(str + i) != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(src) * (i + 1));
	i = 0;
	if (dest == NULL)
		return (NULL);
	else
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
}

struct s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	t_stock_str		*tab;
	int				i;

	tab = malloc(sizeof(t_stock_str) * (ac + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < ac)
	{
		tab[i].str = av[i];
		tab[i].copy = ft_strdup(av[i]);
		tab[i].size = ft_strlen(av[i]);
		i++;
	}
	tab[i].str = 0;
	return (tab);
}

//#include <assert.h>
//#include <string.h>
//void free_tab(t_stock_str *tab) {
//    int i = 0;
//    while (tab[i].str != 0) {
//        free(tab[i].copy);
//        i++;
//    }
//    free(tab);
//}
//int main() {
//	// Test case 1: Normal case
//	char *av1[] = {"Hello", "World"};
//	int ac1 = 2;
//	t_stock_str *result1 = ft_strs_to_tab(ac1, av1);
//	assert(result1 != NULL);
//	assert(strcmp(result1[0].str, "Hello") == 0);
//	assert(strcmp(result1[0].copy, "Hello") == 0);
//	assert(result1[0].size == 5);
//	assert(strcmp(result1[1].str, "World") == 0);
//	assert(strcmp(result1[1].copy, "World") == 0);
//	assert(result1[1].size == 5);
//	assert(result1[2].str == 0);
//	free_tab(result1);
//
//	// Test case 2: Empty strings
//	char *av2[] = {"", ""};
//	int ac2 = 2;
//	t_stock_str *result2 = ft_strs_to_tab(ac2, av2);
//	assert(result2 != NULL);
//	assert(strcmp(result2[0].str, "") == 0);
//	assert(strcmp(result2[0].copy, "") == 0);
//	assert(result2[0].size == 0);
//	assert(strcmp(result2[1].str, "") == 0);
//	assert(strcmp(result2[1].copy, "") == 0);
//	assert(result2[1].size == 0);
//	assert(result2[2].str == 0);
//	free_tab(result2);
//
//	// Test case 3: Single string
//	char *av3[] = {"Single"};
//	int ac3 = 1;
//	t_stock_str *result3 = ft_strs_to_tab(ac3, av3);
//	assert(result3 != NULL);
//	assert(strcmp(result3[0].str, "Single") == 0);
//	assert(strcmp(result3[0].copy, "Single") == 0);
//	assert(result3[0].size == 6);
//	assert(result3[1].str == 0);
//	free_tab(result3);
//
//	printf("All test cases passed!\n");
//	return 0;
//}