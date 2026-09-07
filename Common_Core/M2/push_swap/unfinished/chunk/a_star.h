/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:18:02 by egoh              #+#    #+#             */
/*   Updated: 2025/09/14 08:59:52 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef A_STAR_H
#define A_STAR_H
#include "../stack.h"
#include "move_cost.h"

// from Star - Move Calculation
char		**generate_move_sequence(t_move_cost best, const t_stack *from,
				const t_stack *to, int *out_len);
t_move_cost	evaluate_candidate(const t_stack *from, const t_stack *to,
				int c_pos);

char		**a_star_push(t_stack *from, t_stack *to, t_candidates *candidates,
				int *move_count_out);

bool		pull_B_to_A(t_stack *a, t_stack *b);
bool		push_all_chunks_to_B(t_stack *a, t_stack *b,
				const int *sorted_array, const t_chunks *chunks);

// Debug
void	list_moves(char **moves, const int move_count);
void	list_candidates(const t_stack *s, const t_candidates *candidates);
#endif