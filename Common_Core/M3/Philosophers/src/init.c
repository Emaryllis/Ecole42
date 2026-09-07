/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/05 17:24:53 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		mutex_handler(&table->philos[i].philo_mutex, INIT);
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].full = false;
		table->philos[i].table = table;
		table->philos[i].first_fork = &table->forks[(i + 1) % table->philo_nbr];
		table->philos[i].second_fork = &table->forks[i];
		if (table->philos[i].id % 2 == 0)
		{
			table->philos[i].first_fork = &table->forks[i];
			table->philos[i].second_fork
				= &table->forks[(i + 1) % table->philo_nbr];
		}
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->threads_running_nbr = 0;
	table->end_simulation = false;
	table->threads_ready = false;
	table->philos = btr_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = btr_malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->philos == NULL || table->forks == NULL)
	{
		table->error = true;
		return ;
	}
	mutex_handler(&table->table_mutex, INIT);
	mutex_handler(&table->write_mutex, INIT);
	while (++i < table->philo_nbr)
	{
		mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_debug_id = i;
	}
	return (init_philo(table));
}
