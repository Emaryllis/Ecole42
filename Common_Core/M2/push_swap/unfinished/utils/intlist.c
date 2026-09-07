/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 09:50:28 by egoh              #+#    #+#             */
/*   Updated: 2025/09/14 00:07:42 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "intlist.h"
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_atoi(const char *s, bool *not_int)
{
	int		sign;
	long	r;

	r = 0;
	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		r = r * 10 + *s - '0';
		s++;
		if (sign * r > INT_MAX || sign * r < INT_MIN)
		{
			*not_int = true;
			return (0);
		}
	}
	return (sign * (int)r);
}

int	strlist_count(char **strlist)
{
	int	count;

	count = 0;
	while (strlist && strlist[count] != 0)
		count++;
	return (count);
}

bool	has_duplicate(const int *intlist, int count);

static bool	to_intlist(char **strlist, int **intlist, int count)
{
	int		i;
	char	*p;
	bool	not_int;

	i = 0;
	not_int = false;
	while (i < count)
	{
		p = strlist[i];
		if (*p == '-')
			p++;
		while (*p && ft_isdigit((unsigned char)*p))
			p++;
		if (*p != '\0')
			return (true);
		(*intlist)[i] = ft_atoi(strlist[i], &not_int);
		if (not_int)
			return (true);
		i++;
	}
	return (has_duplicate(*intlist, count));
}

/**
 *
 * @param strlist A string array.
 * @return An integer array allocated with malloc.
 * @return NULL if any string is not a valid integer or if malloc fails.
 */
int	*get_intlist(char **strlist)
{
	int		*intlist;
	int		count;
	bool	error;

	if (!strlist)
		return (NULL);
	count = strlist_count(strlist);
	if (count == 0)
		return (NULL);
	intlist = malloc(sizeof(int) * count);
	if (!intlist)
		return (NULL);
	error = to_intlist(strlist, &intlist, count);
	if (error)
	{
		free(intlist);
		return (NULL);
	}
	return (intlist);
}
