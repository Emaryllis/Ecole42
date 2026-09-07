/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:24:45 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 22:34:53 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CHUNK_H
# define CHUNK_H
# include "../stack.h"
# include <stdbool.h>


typedef struct s_chunk
{
	int	start_index;
	int	end_index;
	int	mid_index;
}		t_chunk;

typedef struct s_chunks
{
    t_chunk	*chunks;
    int     count;
}           t_chunks;

// Stack Utils
int		find_index(const t_stack *s, int value);
int		min_num(const t_stack *s);
int		max_num(const t_stack *s);

// Init
t_chunk	*define_chunks(int len, int chunk_size, int *num_chunks_out);
int		*get_sorted(int *arr, int len);

// Chunk Checks
bool	is_sorted(const t_stack *s);
bool	is_in_chunk(int value_index, t_chunk chunk);

// Chunk Rotations
int		rotations_to_top(const t_stack *s, int candidate_pos);
int		rotations_to_position_in_b(const t_stack *b, int value);

// from Star - Further Optimizations
int	estimate_swap_savings(const t_stack *from, const t_stack *to,
							 int candidate_pos);
#endif
