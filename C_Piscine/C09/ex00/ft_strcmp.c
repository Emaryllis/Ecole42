/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

//#include <assert.h>
//int main(void) {
//	assert(ft_strcmp("abc", "abc") == 0);
//	assert(ft_strcmp("abc", "abcd") < 0);
//	assert(ft_strcmp("abcd", "abc") > 0);
//	assert(ft_strcmp("", "") == 0);
//	assert(ft_strcmp("abc", "") > 0);
//	assert(ft_strcmp("", "abc") < 0);
//	return 0;
//}