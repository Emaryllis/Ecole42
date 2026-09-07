/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <egoh@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:48:05 by egoh              #+#    #+#             */
/*   Updated: 2025/09/14 02:35:04 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../utils/libc/libc.h"
#include "chunk.h"
#include "move_cost.h"
#include <stdlib.h>
/**
 * Determines where the candidate should be inserted.
 * @param s The given stack
 * @param value The candidate value
 * @return A list of positions in the given where the value
 * should be inserted to maintain sorted order.
 */
t_candidates *find_insert_positions(const t_stack *s, int value)
{
	t_candidates *candidates;

	if (!s)
		return (NULL);
	candidates = malloc(sizeof(t_candidates));
	if (!candidates)
		return (NULL);
	if (s->top < 0)
	{
		candidates->positions = ft_calloc(1, sizeof(int));
		if (!candidates->positions)
		{
			free(candidates);
			return NULL;
		}
		candidates->count = 1;
		return candidates;
	}
	candidates->positions = malloc(sizeof(int) * (s->top + 1));
	if (!candidates->positions)
	{
		free(candidates);
		return (NULL);
	}
	candidates->count = 0;
	for (int i = s->top; i >= 0; i--)
	{
		int prev = (i == s->top) ? s->data[0] : s->data[i + 1];
		int curr = s->data[i];
		if (value > curr && value < prev)
			candidates->positions[candidates->count++] = i;
	}
	if (candidates->count == 0)
	{
		free(candidates->positions);
		free(candidates);
		return (NULL);
	}
	return (candidates);
}

/**
 * Returns the positions (indices) of all elements
 * in A that belong to the current chunk.
 * @param a Stack A
 * @param sorted The sorted integer list
 * @param chunk The chunk to check against
 * @return A list of positions in A that belongs to the given chunk
 * @usage Ensures that all chunk values are pushed to Stack B
 */
t_candidates	*positions_in_a(const t_stack *a, const int *sorted,
				const t_chunk chunk)
{
	int				i;
	int				value;
	int				i_sorted;
	t_candidates	*candidates;
	size_t		len;

	if (!a || !sorted)
		return (NULL);
	if (a->top < 0)
		return (NULL);
	candidates = malloc(sizeof(t_candidates));
	if (!candidates)
		return (NULL);
	len = (size_t)a->top + 1;
	candidates->positions = ft_calloc(len, sizeof(int));
	if (!candidates->positions)
		return (free(candidates), NULL);
	candidates->count = 0;
	i = a->top + 1;
	while (--i >= 0)
	{
		value = a->data[i];
		i_sorted = 0;
		while (sorted[i_sorted] != value)
			i_sorted++;
		if (is_in_chunk(i_sorted, chunk))
			candidates->positions[candidates->count++] = i;
	}
	if (candidates->count == 0)
	{
		free(candidates->positions);
		free(candidates);
		return (NULL);
	}
	return (candidates);
}

/**
 * Finds all the possible positions in B where the target
 * value won't affect B's sort order if inserted there.
 * @param b Stack B
 * @param target The target value to insert into B
 * @return All indices in B where inserting
 * the A value would maintain B’s sort order
 */
t_candidates	*positions_in_b(t_stack *b, int target)
{
	int				i;
	int				count;
	t_candidates	*candidates;
	size_t		len;

	if (!b)
		return (NULL);
	if (b->top < 0)
		return (NULL);
	candidates = malloc(sizeof(t_candidates));
	if (!candidates)
		return (NULL);
	len = (size_t)b->top + 1;
	candidates->positions = ft_calloc(len, sizeof(int));
	if (!candidates->positions)
		return (free(candidates), NULL);
	count = 0;
	i = b->top + 1;
	while (--i >= 0)
	{
		if (b->data[i] == target)
			candidates->positions[count++] = i;
	}
	candidates->count = count;
	if (candidates->count == 0)
	{
		free(candidates->positions);
		free(candidates);
		return (NULL);
	}
	return (candidates);
}
