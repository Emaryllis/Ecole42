/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_base_length(char *str)
{
	int	len;
	int	j;

	len = 0;
	while (str[len])
	{
		if (str[len] == '-' || str[len] == '+')
			return (0);
		j = len + 1;
		while (str[j])
		{
			if (str[len] == str[j])
				return (0);
			++j;
		}
		++len;
	}
	if (len < 2)
		return (0);
	return (len);
}

int	check_errors(char *str, char *base)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	while (str[start] != '\0' && (str[start] == ' ' || str[start] == '\t'
			|| str[start] == '\r' || str[start] == '\n' || str[start] == '\v'
			|| str[start] == '\f'))
		start++;
	i = start;
	while (str[i])
	{
		j = 0;
		while (base[j] && (str[i] != base[j] || str[i] == '-' || str[i] == '+'))
			++j;
		if (str[i] != base[j] && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int	get_nb(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	s;
	int	i;
	int	res;
	int	neg;
	int	len;

	len = get_base_length(base);
	if (!len || !check_errors(str, base))
		return (0);
	s = 0;
	while (str[s] != '\0' && (str[s] == ' ' || str[s] == '\t' || str[s] == '\r'
			|| str[s] == '\n' || str[s] == '\v' || str[s] == '\f'))
		s++;
	i = s - 1;
	res = 0;
	neg = 1;
	while (str[++i] && (((str[i] == '-' || str[i] == '+') && i == s)
			|| (str[i] != '-' && str[i] != '+')))
	{
		if (str[i] == '-')
			neg = -1;
		else if (str[i] != '+')
			res = (res * len) + (get_nb(str[i], base));
	}
	return (res * neg);
}

//#include <assert.h>
//int main() {
//	// Test with base 10
//	assert(ft_atoi_base("10", "0123456789") == 10);
//
//	// Test with base 2
//	assert(ft_atoi_base("1010", "01") == 10);
//
//	// Test with base 16
//	assert(ft_atoi_base("A", "0123456789ABCDEF") == 10);
//
//	// Test with base 8
//	assert(ft_atoi_base("12", "01234567") == 10);
//
//	// Test with negative number
//	assert(ft_atoi_base("-10", "0123456789") == -10);
//
//	// Test with invalid string
//	assert(ft_atoi_base("abc", "0123456789") == 0);
//
//	// Test with empty string
//	assert(ft_atoi_base("", "0123456789") == 0);
//	return 0;
//}