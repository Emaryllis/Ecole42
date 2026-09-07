/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

int		ft_strlen(char *str);
int		ft_power(int nb, int pow);
char	*ft_putnbr_base(long int nbr, char *base, int is_neg);

int	check_valid(char *base)
{
	int	base_i;
	int	i;

	base_i = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[base_i])
	{
		i = base_i + 1;
		while (base[i])
		{
			if (base[base_i] == base[i] || base[i] == '+' || base[i] == '-'
				|| base[i] == ' ' || base[i] == '\t' || base[i] == '\n'
				|| base[i] == '\v' || base[i] == '\f' || base[i] == '\r')
				return (0);
			i++;
		}
		base_i++;
	}
	return (1);
}

char	*check_sign(char *str, int *is_neg)
{
	*is_neg = 1;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*is_neg *= -1;
		str++;
	}
	return (str);
}

char	*ft_atoi(char *str, char *base, int *is_neg, int *size)
{
	int	valid_i;
	int	base_i;
	int	valid;

	valid_i = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	str = check_sign(str, is_neg);
	while (*str)
	{
		base_i = -1;
		valid = 0;
		while (base[++base_i])
			if (*str == base[base_i])
				valid = 1;
		if (valid == 0)
			break ;
		str++;
		valid_i++;
	}
	*size = valid_i;
	return (str - valid_i);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long int	num;
	int			sign;
	int			len_num;
	int			pos;
	int			index;

	num = 0;
	pos = 0;
	nbr = ft_atoi(nbr, base_from, &sign, &len_num);
	if (check_valid(base_from) == 0 || check_valid(base_to) == 0)
		return (NULL);
	while (pos < len_num)
	{
		index = 0;
		while (base_from[index] != nbr[pos])
			index++;
		num += index * ft_power(ft_strlen(base_from), (len_num - pos - 1));
		pos++;
	}
	return (ft_putnbr_base(num, base_to, sign));
}

//#include <stdio.h>
//#include <assert.h>
//#include <string.h>
//int main(void)
//{
//    // Test case 1: Conversion from base 10 to base 2
//    char *res = ft_convert_base("10", "0123456789", "01");
//    assert(strcmp(res, "1010") == 0);
//
//    // Test case 2: Conversion from base 2 to base 10
//    res = ft_convert_base("1010", "01", "0123456789");
//    assert(strcmp(res, "10") == 0);
//
//    // Test case 3: Conversion from base 10 to base 16
//    res = ft_convert_base("255", "0123456789", "0123456789ABCDEF");
//    assert(strcmp(res, "FF") == 0);
//
//    // Test case 4: Conversion from base 16 to base 10
//    res = ft_convert_base("FF", "0123456789ABCDEF", "0123456789");
//    assert(strcmp(res, "255") == 0);
//
//    // Test case 5: Conversion with negative number
//    res = ft_convert_base("-10", "0123456789", "01");
//    assert(strcmp(res, "-1010") == 0);
//    printf("All tests passed.\n");
//    return 0;
//}