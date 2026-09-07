/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_chunk_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 06:11:37 by egoh              #+#    #+#             */
/*   Updated: 2025/09/09 20:30:49 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils/libc/libc.h"
#include "chunk/chunk.h"
#include "chunk/a_star.h"
#include <stdlib.h>

#define LOCAL_OPT_SIZE 12  // Maximum chunk top for full A* search

void	sort_three(t_stack *s);
void	small_sort(t_stack *A, t_stack *B);

// Hybrid chunk + full A* sort
void	a_star_chunk_sort(t_stack *A, t_stack *B, int size)
{
	int	*sorted;

	ft_printf("Sorting..."); // Remove when finished
	list_stack(A); // Remove when finished
	list_stack(B); // Remove when finished
	ft_printf("\n"); // Remove when finished
	if (is_sorted(A))
		return ;
	if (size <= 5)
		return (small_sort(A, B));
	// Copy and sort array for chunking

	sorted = get_sorted(A->data, size);
	if (!sorted)
	{
		get_sorted(A->data, size);
		return;
	}

	// Define chunks
	int num_chunks;
	// Adjust chunk top as needed
	t_chunk *chunks = define_chunks(size, size / 5, &num_chunks);
	if (!chunks)
	{
		free(sorted);
		return;
	}

	push_all_chunks_to_B(A, B, sorted, &(t_chunks){chunks, num_chunks});
	ft_printf("\n");

	// Cleanup
	free(sorted);
	free(chunks);
}
