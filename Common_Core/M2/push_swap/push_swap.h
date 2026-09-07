/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 09:50:28 by egoh              #+#    #+#             */
/*   Updated: 2025/10/05 03:42:43 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_hs
{
	int	*keys;
	int	capacity;
}		t_hs;

typedef struct s_intlist
{
	int	*list;
	int	count;
}		t_intlist;

typedef struct s_stack
{
	int	*array;
	int	size;
}	t_stack;

// Operations
void	sa(t_stack *a);
void	ra(t_stack *a);
void	pb(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);

// Sorting algorithms
void	radix_sort(t_stack *a, t_stack *b);
void	small_sort(t_stack *a, t_stack *b);

// utils
int		strlist_count(char **strlist);
int		*get_intlist(char **strlist);
int		*index_array(int *arr, int size);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);

#endif
