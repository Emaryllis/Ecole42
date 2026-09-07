/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <egoh@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:21:13 by egoh              #+#    #+#             */
/*   Updated: 2025/09/13 21:13:59 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STACK_H
# define STACK_H
# include <stdbool.h>

typedef struct s_stack
{
	int		*data;
	int		top;
	int		capacity;
	char	name;
}		t_stack;

void	push(t_stack *from, t_stack *to);
void	swap(t_stack *s, const bool print);
void	rotate(t_stack *s, const bool print);
void	reverse_rotate(t_stack *s, const bool print);
void	swap_both(t_stack *a, t_stack *b);
void	rotate_both(t_stack *a, t_stack *b);
void	reverse_rotate_both(t_stack *a, t_stack *b);
void	execute_moves(char **moves, int move_count, t_stack *a, t_stack *b);

// Debug
void	list_stack(const t_stack *s);
#endif