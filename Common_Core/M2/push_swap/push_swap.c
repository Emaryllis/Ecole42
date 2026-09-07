/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 09:50:28 by egoh              #+#    #+#             */
/*   Updated: 2025/10/05 05:25:16 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static int	get_max_bits(t_stack *stack)
{
	int	max;
	int	bits;

	max = stack->size - 1;
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	i;
	int	j;
	int	size;
	int	num;
	int	max_bits;

	size = a->size;
	max_bits = get_max_bits(a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j++ < size)
		{
			num = a->array[0];
			if (((num >> i) & 1) == 1)
				ra(a);
			else
				pb(a, b);
		}
		while (b->size != 0)
			pa(a, b);
		i++;
	}
}
