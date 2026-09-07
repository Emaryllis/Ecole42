/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:12:48 by egoh              #+#    #+#             */
/*   Updated: 2025/09/12 00:12:48 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
typedef struct s_intlist
{
	int	*list;
	int	count;
}		t_intlist;

int	strlist_count(char **strlist);
int	*get_intlist(char **strlist);