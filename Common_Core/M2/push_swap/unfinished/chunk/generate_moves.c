/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <egoh@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:32:48 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 21:32:48 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "move_cost.h"
#include "../libc/libc.h"
#include "../stack.h"
#include <stdlib.h>

// ---------------------------
// 4️⃣ Append move helper
// ---------------------------
static void	append_move(char ***moves, int *count, const char *move)
{
	(*moves)[*count] = ft_strdup(move);
	(*count)++;
}

// ---------------------------
// 5️⃣ Generate move sequence from best candidate
// ---------------------------
char **generate_move_sequence(t_move_cost best,
                              const t_stack *from,
                              const t_stack *to,
                              int *out_len)
{
    char **moves = malloc(sizeof(char *) * (best.rot_from + best.rot_to + 10));
    int count = 0;

    // Decide rotation labels based on stack names
    const char *rot_from = (from->name == 'a') ? "ra"  : "rb";
    const char *rrot_from = (from->name == 'a') ? "rra" : "rrb";

    const char *rot_to   = (to->name == 'a') ? "ra"  : "rb";
    const char *rrot_to  = (to->name == 'a') ? "rra" : "rrb";

    const char *double_rot = (from->name == 'a' && to->name == 'b') ? "rr"
                              : (from->name == 'b' && to->name == 'a') ? "rr"
                              : "rr"; // (can refine if you want symmetrical rr/rrr)
    const char *double_rrot = "rrr"; // same idea

    // Apply double rotations first
    for (int i = 0; i < best.double_rot; i++)
        append_move(&moves, &count, (best.rot_from <= best.rot_to) ? double_rot : double_rrot);

    // Remaining rotations in "from"
    for (int i = 0; i < best.rot_from - best.double_rot; i++)
        append_move(&moves, &count, (best.rot_from <= best.rot_to) ? rot_from : rrot_from);

    // Remaining rotations in "to"
    for (int i = 0; i < best.rot_to - best.double_rot; i++)
        append_move(&moves, &count, (best.rot_from <= best.rot_to) ? rot_to : rrot_to);

    if (best.swap_bonus)
        append_move(&moves, &count, "ss");

    // Final push: pb if going into B, pa if going into A
    append_move(&moves, &count, (to->name == 'b') ? "pb" : "pa");

    *out_len = count;
    return moves;
}
