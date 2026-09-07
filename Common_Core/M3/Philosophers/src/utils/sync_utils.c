/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/05 20:04:20 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../main.h"

/**
 * Spinlock until all threads are ready
 */
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->threads_ready))
		;
}

bool	all_threads_running(t_mtx *mutex, const long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	mutex_handler(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	mutex_handler(mutex, UNLOCK);
	return (ret);
}

void	desync_philos(t_philo *philo, void (*thinking)(t_philo *, bool))
{
	if (philo->table->philo_nbr % 2 == 0 && philo->id % 2 == 0)
		btr_usleep(3e4, philo->table);
	else if (philo-> id % 2)
		thinking(philo, false);
}
