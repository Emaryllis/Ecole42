/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:59 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 22:34:48 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "chunk.h"

/**
 * @param value_index The index to check
 * @param chunk The chunk to check against
 * @return true if the value_index is within the
 * given chunk boundaries, false otherwise
 * @see this.has_values_in_chunk() & positions.positions_in_a()
 */
bool	is_in_chunk(int value_index, t_chunk chunk)
{
	return (value_index >= chunk.start_index && value_index <= chunk.end_index);
}

/**
 * @param s The stack to check against
 * @return true if the stack is sorted in ascending order, false otherwise
 * @usage Prevents already sorted input from being processed
 */
bool	is_sorted(const t_stack *s)
{
	int	i;

	i = s->top + 1;
	while (--i > 0)
	{
		if (s->data[i] > s->data[i - 1])
			return (false);
	}
	return (true);
}
