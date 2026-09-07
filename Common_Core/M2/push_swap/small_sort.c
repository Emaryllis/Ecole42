/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 09:50:28 by egoh              #+#    #+#             */
/*   Updated: 2025/09/11 22:17:15 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static void	rra(t_stack *a)
{
	int	last;
	int	i;

	if (a->size < 2)
		return ;
	last = a->array[a->size - 1];
	i = a->size - 1;
	while (i > 0)
	{
		a->array[i] = a->array[i - 1];
		i--;
	}
	a->array[0] = last;
	ft_putstr_fd("rra\n", STDOUT_FILENO);
}

static void	sort_three(t_stack *a)
{
	int	*s;

	s = a->array;
	if (s[0] > s[1] && s[1] < s[2] && s[0] < s[2])
		sa(a);
	else if (s[0] > s[1] && s[1] > s[2])
	{
		sa(a);
		rra(a);
	}
	else if (s[0] > s[1] && s[1] < s[2] && s[0] > s[2])
		ra(a);
	else if (s[0] < s[1] && s[1] > s[2] && s[0] < s[2])
	{
		sa(a);
		ra(a);
	}
	else if (s[0] < s[1] && s[1] > s[2] && s[0] > s[2])
		rra(a);
}

static void	sort_four_five(t_stack *a, t_stack *b)
{
	int	min_index;
	int	i;

	while (a->size > 3)
	{
		min_index = 0;
		i = 1;
		while (i < a->size)
		{
			if (a->array[i] < a->array[min_index])
				min_index = i;
			i++;
		}
		if (min_index <= a->size / 2)
			while (min_index-- > 0)
				ra(a);
		else
			while (min_index++ < a->size)
				rra(a);
		pb(a, b);
	}
	sort_three(a);
	while (b->size > 0)
		pa(a, b);
}

void	small_sort(t_stack *a, t_stack *b)
{
	if (a->size == 2 && a->array[0] > a->array[1])
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4 || a->size == 5)
		sort_four_five(a, b);
}
