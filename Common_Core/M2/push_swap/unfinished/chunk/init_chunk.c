/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <egoh@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:15:39 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 20:15:39 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils/libc/libc.h"
#include "chunk.h"
#include <stdlib.h>

/**
 * Allocates chunks based on chunk top & no of numbers.
 * Computes the start, end & mid-index of each chunk.
 * The start & end index of each chunk represents its
 * boundaries, while the mid-index is the index of
 * the midpoint of the chunk.
 * @param len No of integers
 * @param chunk_size The desired chunk top
 * @param num_chunks_out RETURNS: The no of chunks created
 * @return A list of chunk information & the no of
 * chunks through [num_chunks_out]
 */
t_chunk	*define_chunks(int len, int chunk_size, int *num_chunks_out)
{
	int		i;
	int		num_chunks;
	t_chunk	*chunks;

	i = -1;
	num_chunks = (len + chunk_size - 1) / chunk_size;
	chunks = malloc(sizeof(t_chunk) * num_chunks);
	if (chunks == NULL)
		return (NULL);
	while (++i < num_chunks)
	{
		chunks[i].start_index = i * chunk_size;
		chunks[i].end_index = (i + 1) * chunk_size - 1;
		if (chunks[i].end_index >= len)
			chunks[i].end_index = len - 1;
		chunks[i].mid_index = (chunks[i].start_index + chunks[i].end_index) / 2;
	}
	*num_chunks_out = num_chunks;
	return (chunks);
}

/**
 * Duplicates and sorts an integer list using insertion sort.
 * @param arr The integer list
 * @param len No of integers
 * @return A duplicated sorted version of the integer list
 */
int	*get_sorted(int *arr, int len)
{
	int	*sorted;
	int	key;
	int	i;
	int	j;

	sorted = malloc(sizeof(int) * len);
	if (!sorted)
		return (NULL);
	ft_memcpy(sorted, arr, sizeof(int) * len);
	i = 0;
	while (++i < len)
	{
		key = arr[i];
		j = i;
		while (--j >= 0 && arr[j] > key)
			arr[j + 1] = arr[j];
		arr[j + 1] = key;
	}
	return (sorted);
}
