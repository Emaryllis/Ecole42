/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/05 16:48:38 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../main.h"

int	send_error(const char *error)
{
	printf(RD"❌ %s\n"RST, error);
	return (-1);
}

void	*btr_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		send_error("Malloc Error.");
		return (NULL);
	}
	return (ptr);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
