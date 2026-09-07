/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/05 19:48:29 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static void	eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG);
	mutex_handler(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG);
	if (DEBUG)
		printf("[D] Philosopher %d is starting to eat meal %d/%ld.\n",
			philo->id, philo->meals_counter + 1,
			philo->table->nbr_limit_meals);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG);
	btr_usleep(philo->table->time_to_eat, philo->table);
	if (DEBUG)
		printf("[D] Philosopher %d has finished eating meal %d/%ld.\n",
			philo->id, philo->meals_counter, philo->table->nbr_limit_meals);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
	{
		write_status(SLEEPING, philo, DEBUG);
		set_bool(&philo->philo_mutex, &philo->full, true);
	}
	mutex_handler(&philo->first_fork->fork, UNLOCK);
	mutex_handler(&philo->second_fork->fork, UNLOCK);
}

void	*lone_philo(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	if (DEBUG)
		printf("[D] Lone Philosopher %d waiting...\n", philo->id);
	wait_all_threads(philo->table);
	set_long(&table->table_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex, &table->threads_running_nbr);
	if (DEBUG)
		printf("[D] Lone Philosopher %d starting simulation...\n", philo->id);
	write_status(TAKE_FIRST_FORK, philo, DEBUG);
	if (DEBUG)
		printf("[D] Lone Philosopher %d has taken the only fork...\n",
			philo->id);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	thinking(t_philo *philo, bool start)
{
	long	think;

	if (start)
		write_status(THINKING, philo, DEBUG);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	think = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (think < 0)
		think = 0;
	btr_usleep(think / 2, philo->table);
}

void	*simulation(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&table->table_mutex, &table->threads_running_nbr);
	desync_philos(philo, thinking);
	while (!simulation_finished(table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG);
		if (DEBUG)
			printf("[D] Philosopher %d is now sleeping...\n", philo->id);
		btr_usleep(table->time_to_sleep, table);
		thinking(philo, true);
	}
	write_status(SLEEPING, philo, DEBUG);
	if (DEBUG)
		printf("[D] Philosopher %d has finished.\n", philo->id);
	return (NULL);
}

/**
 * Starts the dinner simulation by creating philosopher threads
 */
void	start_dinner(t_table *table)
{
	int		i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		thread_handler(&table->philos[0].thread_id, lone_philo,
			&table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			thread_handler(&table->philos[i].thread_id, simulation,
				&table->philos[i], CREATE);
	}
	thread_handler(&table->monitor_id, monitor, table, CREATE);
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		thread_handler(&table->philos[i].thread_id, NULL,
			NULL, JOIN);
	thread_handler(&table->monitor_id, NULL, NULL, JOIN);
}
