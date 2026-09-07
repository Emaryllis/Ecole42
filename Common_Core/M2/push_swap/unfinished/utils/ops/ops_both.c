/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_both.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:04:42 by egoh              #+#    #+#             */
/*   Updated: 2025/09/11 22:22:12 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libc/libc.h"
#include "../../stack.h"

void	swap_both(t_stack *a, t_stack *b)
{
	list_stack(a); // Remove when finished
	list_stack(b); // Remove when finished
	swap(a, false);
	swap(b, false);
	ft_printf("ss | "); // Change to ss\n when done.
	list_stack(a); // Remove when finished
	list_stack(b); // Remove when finished
	ft_printf("\n");
}

void	rotate_both(t_stack *a, t_stack *b)
{
	list_stack(a); // Remove when finished
	list_stack(b); // Remove when finished
	rotate(a, false);
	rotate(b, false);
	ft_printf("rr | "); // Change to rr\n when done.
	list_stack(a); // Remove when finished
	list_stack(b); // Remove when finished
	ft_printf("\n");
}

void	reverse_rotate_both(t_stack *a, t_stack *b)
{
	list_stack(a); // Remove when finished
	list_stack(b); // Remove when finished
	reverse_rotate(a, false);
	reverse_rotate(b, false);
	ft_printf("rrr | "); // Change to rrr\n when done.
	list_stack(a); // Remove when finished
	list_stack(b); // Remove when finished
	ft_printf("\n");
}
