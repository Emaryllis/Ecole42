/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:34:15 by egoh              #+#    #+#             */
/*   Updated: 2025/09/09 22:34:30 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../chunk/chunk.h"

int	find_index(const t_stack *s, int value)
{
	for (int i = s->top; i > 0; i--)
		if (s->data[i] == value)
			return i;
	return 0;
}

int min_num(const t_stack *s)
{
	int min = s->data[s->top];
	for (int i = s->top - 1; i > 0; i--)
		if (s->data[i] < min)
			min = s->data[i];
	return min;
}

int max_num(const t_stack *s)
{
	int max = s->data[s->top];
	for (int i = s->top - 1; i > 0; i--)
		if (s->data[i] > max)
			max = s->data[i];
	return max;
}