/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/11 22:31:24 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static void	is_all_full(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (!get_bool(&table->philos[i].philo_mutex, &table->philos[i].full))
			return ;
	}
	set_bool(&table->table_mutex, &table->end_simulation, true);
}

static bool	philo_died(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISECOND)
		- get_long(&philo->philo_mutex, &philo->last_meal_time);
	return (elapsed > philo->table->time_to_die / 1e3);
}

void	*monitor(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i, DEBUG);
			}
		}
		is_all_full(table);
		btr_usleep(1e3, table);
	}
	if (DEBUG)
		printf("[D] Monitor thread ending...\n");
	return (NULL);
}
