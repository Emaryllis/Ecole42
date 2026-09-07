/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:39:15 by egoh              #+#    #+#             */
/*   Updated: 2025/09/07 11:24:08 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../utils/libc/libc.h"
#include "stack.h"
#include <stdlib.h>

static t_stack	init_stack_a(const int *intlist, int count)
{
	t_stack	a;
	int		i;

	a.top = count - 1;
	a.data = malloc(sizeof(int) * count);
	a.name = 'a';
	a.capacity = count;
	if (!a.data)
		return (a);
	i = -1;
	while (++i < count)
		a.data[count - 1 - i] = intlist[i];
	return (a);
}

static t_stack	init_stack_b(int count)
{
	t_stack	b;

	b.top = -1;
	b.name = 'b';
	b.data = ft_calloc(count, sizeof(int));
	b.capacity = count;
	return (b);
}

void	a_star_chunk_sort(t_stack *A, t_stack *B, int size);

void	init_data(int *intlist, int count)
{
	t_stack	a;
	t_stack	b;

	a = init_stack_a(intlist, count);
	if (!a.data)
		return ;
	b = init_stack_b(count);
	if (!b.data)
	{
		free(a.data);
		return ;
	}
	if (count > 1)
		a_star_chunk_sort(&a, &b, count);
	free(a.data);
	free(b.data);
}
