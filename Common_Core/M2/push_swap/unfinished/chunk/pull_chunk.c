/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:52:36 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 22:34:20 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "a_star.h"
#include "../utils/libc/libc.h"
#include <stdlib.h>
#include <limits.h>

static void	free_candidates_move(t_candidates *candidates, char **moves,
								 int move_count)
{
	int i;

	i = -1;
	if (candidates)
	{
		free(candidates->positions);
		free(candidates);
	}
	if (moves)
	{
		while (++i < move_count)
			free(moves[i]);
		free(moves);
	}

}

bool	pull_B_to_A(t_stack *a, t_stack *b)
{
	// Get all positions of the largest value in B
	t_candidates *candidates = positions_in_b(b, max_num(b));
	char **moves = NULL;
	int move_count = 0;
	if (!candidates)
		return true; // nothing to do for this chunk

	ft_printf("\n---| Pulling: ");
	list_stack(b);
	ft_printf("---\n");

	while (candidates && candidates->count != 0)
	{
		if (candidates->count == 1)
		{
			push(b, a);
			free_candidates_move(candidates, moves, move_count);
			return true;
		}

		// Debug: print candidates
		list_candidates(a, candidates);

		// Generate minimal-cost move sequence for this target
		move_count = 0;
		moves = a_star_push(b, a, candidates, &move_count);

		// Debug: print moves
		list_moves(moves, move_count);

		if (move_count == -1)
		{
			// malloc failure: free resources and propagate failure
			free_candidates_move(candidates, moves, move_count);
			return false;
		}

		// Execute the move sequence
		execute_moves(moves, move_count, a, b);

		free_candidates_move(candidates, moves, move_count);
		// Get all positions of the largest value in B
		candidates = positions_in_b(b, max_num(b));
	}
	ft_printf("\n");
	if (candidates)
		free_candidates_move(candidates, NULL, 0);
	return true;
}