/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 09:50:28 by egoh              #+#    #+#             */
/*   Updated: 2025/10/05 05:24:47 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stdint.h>

static void	ft_bzero(void *s, size_t len) // Just memset but always 0
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (len--)
		*ptr++ = 0;
}

void	*ft_calloc(size_t amt, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (amt == 0 || size == 0)
		return (malloc(1));
	if (amt > SIZE_MAX / size)
		return (NULL);
	total_size = amt * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}

static t_stack	init_stack_a(int *intlist, int count)
{
	t_stack	a;

	a.array = index_array(intlist, count);
	a.size = count;
	return (a);
}

static t_stack	init_stack_b(int count)
{
	t_stack	b;

	b.array = ft_calloc(count, sizeof(int));
	b.size = 0;
	return (b);
}

void	init_data(int *intlist, int count)
{
	t_stack	a;
	t_stack	b;

	a = init_stack_a(intlist, count);
	if (!a.array)
		return ;
	b = init_stack_b(count);
	if (!b.array)
	{
		free(a.array);
		return ;
	}
	if (count > 0 && count <= 5)
		small_sort(&a, &b);
	else if (count > 5)
		radix_sort(&a, &b);
	free(a.array);
	free(b.array);
}
