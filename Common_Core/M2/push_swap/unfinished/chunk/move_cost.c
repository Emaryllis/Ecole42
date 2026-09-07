/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <egoh@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:31:09 by egoh              #+#    #+#             */
/*   Updated: 2025/09/17 01:41:08 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "a_star.h"
#include "../utils/libc/libc.h"
#include <stdlib.h>
#include <limits.h>

/**
 * Calculates the minimal rotations to bring the element at index
 * to the top of the given stack.
 * @param s The stack to evaluate
 * @param index The candidate index
 * @return The minimal amount of rotations. A positive integer represents
 * forward rotations, while a negative integer represents reverse rotations.
 */
int rotations_to_top(const t_stack *s, int index)
{
    int forward = s->top - index; // ra count to bring index to top
    int reverse = index + 1;      // rra count to bring index to top
    return (forward <= reverse) ? forward : reverse;
}

/**
 * Calculates the move cost of bringing a candidate
 * from Stack "from" to Stack "to".
 * @param from Stack "from"
 * @param to Stack "to"
 * @param c_pos The candidate position (indices) of Stack "from"
 * @return
 */
t_move_cost evaluate_candidate(const t_stack *from, const t_stack *to,
							   int c_pos)
{
	t_move_cost	best;
	t_candidates *insert_positions = find_insert_positions(to, from->data[c_pos]);
	if (!insert_positions)
	{
		ft_printf("Failed to find insert positions for %d (%d).\n",
				  from->data[c_pos], c_pos, to->name);
		best.total_cost = -1;
		return best;
	}
	best.total_cost = INT_MAX;
	best.candidate_index = c_pos;
	for (int i = 0; i < insert_positions->count; i++)
	{
		t_move_cost current;
		current.candidate_index = insert_positions->positions[i];
		current.rot_from = rotations_to_top(from, c_pos);
		current.rot_to = rotations_to_top(to, insert_positions->positions[i]);
		current.double_rot = ft_min(current.rot_from, current.rot_to);
		current.swap_bonus = 0; //estimate_swap_savings(from, to, candidate_pos);
		current.total_cost = current.rot_from + current.rot_to - current.double_rot - current.swap_bonus;
		if (current.total_cost < best.total_cost)
			best = current;
	}

	free(insert_positions->positions);
	free(insert_positions);
	return best;
}

/**
 * @param from Stack from
 * @param to Stack to
 * @param candidates A list of candidate positions from Stack "from"
 * @return The move cost of the best candidate
 * @see positions.positions_in_a() & positions.positions_in_b()
 * for how candidates is populated
 */
t_move_cost choose_best_candidate(const t_stack *from, const t_stack *to,
								  t_candidates *candidates)
{
	t_move_cost best;
	best.total_cost = INT_MAX;

	for (int i = 0; i < candidates->count; i++)
	{
		// skip candidate already at top (or any other early-exit logic)
		if (candidates->positions[i] == from->top)
			continue;

		ft_printf("Evaluating %d-%d\n",
			from->data[candidates->positions[i]], candidates->positions[i]);
		t_move_cost current = evaluate_candidate(from, to, candidates->positions[i]);
		if (current.total_cost == -1)
		{
			best.total_cost = -1;
			return best;
		}
		if (current.total_cost < best.total_cost)
			best = current;
	}

	return best;
}

/**
 * @param from Stack to pull from
 * @param to Stack to push to
 * @param candidates A list of candidate positions from Stack "from"
 * @param move_count_out RETURNS: No of moves (If stack "to" is sorted,
 * it will be 0. For malloc errors, it will be -1.)
 * @return The least amount of ops needed to
 * transfer from stack "from" to stack "to"
 * @see positions.positions_in_a() & positions.positions_in_b()
 * for how candidates is populated
 */
char **a_star_push(t_stack *from, t_stack *to, t_candidates *candidates,
				   int *move_count_out)
{
	t_move_cost best = choose_best_candidate(from, to, candidates);
	if (best.total_cost == -1)
	{
		*move_count_out = -1;
		return (NULL);
	}
	// If no valid candidate found, return empty move list
	if (best.total_cost == INT_MAX)
	{
		*move_count_out = 0;
		return (NULL);
	}
	ft_printf("Best: %d (%d), Total Cost: %d, ",
			  from[best.candidate_index], best.candidate_index, best.total_cost);

	return generate_move_sequence(best, from, to, move_count_out);
}