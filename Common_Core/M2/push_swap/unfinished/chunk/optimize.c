/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <egoh@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:10:35 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 21:10:35 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../stack.h"

// Smarter estimate_swap_savings
// Only suggests swaps if it actually improves candidate placement
int estimate_swap_savings(const t_stack *from, const t_stack *to, int candidate_pos)
{
	int from_swap = 0;
	int to_swap = 0;
	int candidate_value = to->data[candidate_pos];

	// Check top two of 'from' stack
	if (from->top >= 1)
	{
		int top = from->data[from->top];
		int next = from->data[from->top - 1];

		// Swap only if candidate fits better in descending order
		if ((candidate_value < top && candidate_value > next) ||
			(top < next && (candidate_value < top || candidate_value > next)))
			from_swap = 1;
	}

	// Check top two of 'to' stack
	if (to->top >= 1 && (candidate_pos == to->top || candidate_pos == to->top - 1))
	{
		int top = to->data[to->top];
		int next = to->data[to->top - 1];

		if ((candidate_value < top && candidate_value > next) ||
			(top < next && (candidate_value < top || candidate_value > next)))
			to_swap = 1;
	}

	// If both benefit, use ss
	if (from_swap && to_swap)
		return 1; // ss replaces sa+sb
	else
		return from_swap + to_swap; // either 0 or 1
}
