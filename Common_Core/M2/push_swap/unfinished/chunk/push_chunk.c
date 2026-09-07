/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_chunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <egoh@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:36:52 by egoh              #+#    #+#             */
/*   Updated: 2025/09/16 21:38:46 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../utils/libc/libc.h"
#include "a_star.h"
#include <stdlib.h>

static	void free_candidates_move(t_candidates *candidates, char **moves, int move_count)
{
	int i;

	i = -1;
	if (candidates)
	{
		if (candidates->positions)
			free(candidates->positions);
		free(candidates);
	}
	if (moves && move_count > 0)
	{
		while (++i < move_count)
		{
			if (moves[i])
				free(moves[i]);
		}
		free(moves);
	}
}

/**
 *
 * @param a Stack A
 * @param b Stack B
 * @param sorted The sorted integer list
 * @param chunk The chunk to sort
 * @return true if no errors, false if there is a malloc error
 */
static bool push_chunk_to_B(t_stack *a, t_stack *b, const int *sorted, t_chunk chunk)
{
    t_candidates *candidates = positions_in_a(a, sorted, chunk);
	char **moves = NULL;
	int move_count;
    if (!candidates)
        return true; // nothing to do for this chunk

	ft_printf("\n---| Pushing Chunk [%d - %d] |---\n",
		sorted[chunk.start_index], sorted[chunk.end_index]);

    while (candidates && candidates->count != 0)
    {
    	if (candidates->count == 1)
    	{
    		push(a, b);
    		free_candidates_move(candidates, NULL, 0);
    		return true;
    	}

        // Debug: print candidates
		list_candidates(a, candidates);

    	// Get moves
		move_count = 0;
        moves = a_star_push(a, b, candidates, &move_count);

        // Debug: print moves (moves may be NULL when move_count <= 0)
    	list_moves(moves, move_count);

        if (move_count == -1)
        {
            // malloc failure: free resources and propagate failure
			free_candidates_move(candidates, moves, move_count);
            return false;
        }

        if (move_count == 0)
        {
            // Candidate at top of A and not considered movable by A* -> force push one item
            // (We must free current candidates/moves **before** re-fetching new candidates.)

            push(a, b);
            int pushed_value = b->data[b->top];
            if (pushed_value <= sorted[chunk.mid_index])
                rotate(b, true);

            // free current allocated structures and re-evaluate remaining candidates
			free_candidates_move(candidates, moves, move_count);
            candidates = positions_in_a(a, sorted, chunk);
            continue;
        }

        // Normal case: execute the moves that A* returned
        execute_moves(moves, move_count, a, b);

        // After pushing, semi-sort b using chunk midpoint (pushed_value now at top)
        int pushed_value = b->data[b->top];
        if (pushed_value <= sorted[chunk.mid_index])
            rotate(b, true);

        // Free and re-fetch candidates for next iteration
		free_candidates_move(candidates, moves, move_count);
        candidates = positions_in_a(a, sorted, chunk);
    }
	ft_printf("\n");
    // ensure we don't leak if positions_in_a returned NULL initially
    if (candidates)
		free_candidates_move(candidates, NULL, 0);
    return true;
}

bool push_all_chunks_to_B(t_stack *a, t_stack *b, const int *sorted_array,
						  const t_chunks *chunks)
{
    int i;

    i = -1;
    while (++i < chunks->count)
	{
		if (!push_chunk_to_B(a, b, sorted_array, chunks->chunks[i]))
			return (false);
		pull_B_to_A(a, b);
	}
	return (true);
}