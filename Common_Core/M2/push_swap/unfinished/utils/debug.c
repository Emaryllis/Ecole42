/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:49:10 by egoh              #+#    #+#             */
/*   Updated: 2025/09/16 21:40:18 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "move_cost.h"
#include "../libc/libc.h"
#include "stack.h"

void list_stack(const t_stack *s)
{
	if (s)
	{
		ft_printf("Stack %c~%d: ", s->name, s->top + 1);
		if (s->top < 0)
		{
			ft_printf("Empty. | ");
			return;
		}
		for (int i = s->top; i >= 1; i--)
		{
			ft_printf("%d,", s->data[i]);
		}
		ft_printf("%d ", s->data[0]);
		ft_printf("| ");
	}
	else
		ft_printf("| Invalid stack. | ");
}

void list_moves(char **moves, const int move_count)
{
	if (moves && move_count > 0) {
		ft_printf("Best Moves (%d): ", move_count);
		for (int i = 0; i < move_count; i++)
			ft_printf("%s ", moves[i]);
		ft_printf("\n");
	}
	else
		ft_printf("Best Moves: NULL (%d)\n", move_count);
}

void list_candidates(const t_stack *s, const t_candidates *candidates)
{
	if (s && candidates && candidates->positions)
	{
		ft_printf("|Stack %c: ",s->name);
		if (candidates->count == 0)
		{
			ft_printf("Empty. | ");
			return;
		}
		for (int i = 0; i < candidates->count - 1; i++)
			ft_printf("%d,", s->data[candidates->positions[i]]);
		ft_printf("%d", s->data[candidates->positions[candidates->count - 1]]);
		ft_printf(" (");
		for (int i = 0; i < candidates->count - 1; i++)
			ft_printf("%d,", candidates->positions[i]);
		ft_printf("%d", candidates->positions[candidates->count - 1]);
		ft_printf(") | ");
	}
	else
		ft_printf("| No candidates found iStack %c: NULL | ", s ? s->name : '?');
}