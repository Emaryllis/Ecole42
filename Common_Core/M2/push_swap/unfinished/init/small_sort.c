/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:44:40 by egoh              #+#    #+#             */
/*   Updated: 2025/09/11 22:17:15 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stack.h"

void	sort_three(t_stack *s)
{
	int	a;
	int	b;
	int	c;

	a = s->data[s->top];
	b = s->data[s->top - 1];
	c = s->data[s->top - 2];
	if (a < b && b < c)
		return ;
	if (a > b && b < c && a < c)
		swap(s, true);
	else if (a > b && b > c)
	{
		swap(s, true);
		reverse_rotate(s, true);
	}
	else if (a > b && b < c && a > c)
		rotate(s, true);
	else if (a < b && b > c && a < c)
	{
		swap(s, true);
		rotate(s, true);
	}
	else if (a < b && b > c && a > c)
		reverse_rotate(s, true);
}

static void	sort_four_five(t_stack *A, t_stack *B)
{
	int	size;
	int	top_b;

	push(A, B);
	size = A->top + 1;
	if (size == 5)
		push(A, B);
	sort_three(A);
	while (B->top >= 0)
	{
		top_b = B->data[B->top];
		push(B, A);
		if (top_b > A->data[A->top - 1] && top_b > A->data[0])
			rotate(A, true);
		else if (A->data[A->top] > A->data[A->top - 1])
			swap(A, true);
	}
}

// Helper for small dataset
void	small_sort(t_stack *A, t_stack *B)
{
	if (A->top == 1 && A->data[A->top] > A->data[A->top - 1])
		swap(A, true);
	else if (A->top == 2)
		sort_three(A);
	else if (A->top == 3 || A->top == 4)
		sort_four_five(A, B);
}
