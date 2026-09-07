/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unique.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:35:32 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 23:35:32 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "hashset.h"
#include "intlist.h"
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

// 1. Hash function
uint32_t	hash(int key, int capacity)
{
	return ((uint32_t)(key) % capacity);
}

// 2. Create hash set
t_hashset	*create_hashset(int capacity)
{
	int		i;
	t_hashset	*set;

	set = malloc(sizeof(t_hashset));
	set->capacity = capacity;
	set->keys = malloc(sizeof(int) * capacity);
	i = 0;
	while (i < capacity)
		set->keys[i++] = INT_MIN;
	return (set);
}

// 3. Check contains
bool	contains(t_hashset *set, int key)
{
	uint32_t	idx;

	idx = hash(key, set->capacity);
	while (set->keys[idx] != INT_MIN)
	{
		if (set->keys[idx] == key)
			return (true);
		idx = (idx + 1) % set->capacity;
	}
	return (false);
}

// 4. Insert key
void	insert(t_hashset *set, int key)
{
	uint32_t	idx;

	idx = hash(key, set->capacity);
	while (set->keys[idx] != INT_MIN)
	{
		if (set->keys[idx] == key)
			return ;
		idx = (idx + 1) % set->capacity;
	}
	set->keys[idx] = key;
}

/**
 * Check for duplicates in an integer list using a hash set.
 * Does not check for a null intlist since it's expected
 * to be called with a valid list.
 * @param intlist The integer list
 * @param count No of integers
 * @return true if duplicates exist, false otherwise
 */
bool	has_duplicate(const int *intlist, int count)
{
	int		i;
	t_hashset	*set;

	set = create_hashset(count * 2);
	i = 0;
	while (i < count)
	{
		if (contains(set, intlist[i]))
		{
			free(set->keys);
			free(set);
			return (true);
		}
		insert(set, intlist[i++]);
	}
	free(set->keys);
	free(set);
	return (false);
}
