/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cost.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <egoh@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:12:10 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 19:12:10 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MOVE_COST_H
# define MOVE_COST_H
# include "chunk.h"

typedef struct s_move_cost
{
	int	candidate_index;
	int	rot_from;
	int	rot_to;
	int	double_rot;
	int	swap_bonus;
	int	total_cost;
}		t_move_cost;

typedef struct s_candidates
{
	int	*positions;
	int	count;
}		t_candidates;

// Chunk Positions
t_candidates	*find_insert_positions(const t_stack *s, int value);
t_candidates 	*positions_in_a(const t_stack *a, const int *sorted,
								const t_chunk chunk);
t_candidates	*positions_in_b(t_stack *b, int target);

#endif