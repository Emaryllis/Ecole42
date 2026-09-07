/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:45:04 by egoh              #+#    #+#             */
/*   Updated: 2025/09/11 18:35:03 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libc/libc.h"
#include "../../stack.h"

void	push(t_stack *from, t_stack *to)
{
	if (from->top < 0)
		return ;
	list_stack(from); // Remove when finished
	list_stack(to); // Remove when finished
	to->data[++to->top] = from->data[from->top--];
	ft_printf("p%c | ", to->name); // Change to p%\n when done.
	list_stack(from); // Remove when finished
	list_stack(to); // Remove when finished
	ft_printf("\n"); // Remove when finished
}

void	swap(t_stack *s, const bool print)
{
	int	tmp;

	if (s->top < 1)
		return ;
	if (print) list_stack(s); // Remove when finished
	tmp = s->data[s->top];
	s->data[s->top] = s->data[s->top - 1];
	s->data[s->top - 1] = tmp;
	if (print)
		ft_printf("s%c | ", s->name); // Change to s%c\n when done.
	if (print) list_stack(s); // Remove when finished
	if (print) ft_printf("\n"); // Remove when finished
}

void	rotate(t_stack *s, const bool print)
{
	int	tmp;
	int	i;

	if (s->top < 1)
		return ;
	if (print) list_stack(s); // Remove when finished
	tmp = s->data[s->top];
	i = s->top + 1;
	while (--i > 0)
		s->data[i] = s->data[i - 1];
	s->data[0] = tmp;
	if (print)
		ft_printf("r%c | ", s->name); // Change to r%c\n when done.
	if (print) list_stack(s); // Remove when finished
	if (print) ft_printf("\n"); // Remove when finished
}

void	reverse_rotate(t_stack *s, const bool print)
{
	int	tmp;
	int	i;

	if (s->top < 1)
		return ;
	if (print) list_stack(s); // Remove when finished
	tmp = s->data[0];
	i = -1;
	while (++i < s->top)
		s->data[i] = s->data[i + 1];
	s->data[s->top] = tmp;
	if (print)
		ft_printf("rr%c | ", s->name); // Change to rr%c\n when done.
	if (print) list_stack(s); // Remove when finished
	if (print) ft_printf("\n"); // Remove when finished
}
