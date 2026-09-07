/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <egoh@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:09:29 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 18:09:29 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../stack.h"
#include "../libc/libc.h"

static void	do_ops(t_stack *a, t_stack *b, char *move)
{

	if (!ft_strcmp(move, "sa"))
		return (swap(a, true));
	else if (!ft_strcmp(move, "sb"))
		return (swap(b, true));
	else if (!ft_strcmp(move, "ss"))
		return (swap_both(a, b));
	else if (!ft_strcmp(move, "pa"))
		return (push(b, a));
	else if (!ft_strcmp(move, "pb"))
		return (push(a, b));
	else if (!ft_strcmp(move, "ra"))
		return (rotate(a, true));
	else if (!ft_strcmp(move, "rb"))
		return (rotate(b, true));
	else if (!ft_strcmp(move, "rr"))
		return (rotate_both(a, b));
	else if (!ft_strcmp(move, "rra"))
		return (reverse_rotate(a, true));
	else if (!ft_strcmp(move, "rrb"))
		return (reverse_rotate(b, true));
	else if (!ft_strcmp(move, "rrr"))
		return (reverse_rotate_both(a, b));
	ft_printf("Got: %s. Expected: sa,sb,ss,pa,pb,ra,rb,rr,rra,rrb,rrr",
		move);
}

void	execute_moves(char **moves, int move_count, t_stack *a, t_stack *b)
{
	int	i;

	i = -1;
	while (++i < move_count)
		do_ops(a, b, moves[i]);
}
