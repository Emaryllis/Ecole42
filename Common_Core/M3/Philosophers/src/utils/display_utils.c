/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/07 16:30:22 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../main.h"

void	fork_debug(t_status status, t_philo *philo, long elapsed, bool debug)
{
	if (!debug)
		printf(W"%-6ld"M" %d has taken a fork\n"RST, elapsed, philo->id);
	else if (status == TAKE_FIRST_FORK)
		printf(W"%-6ld"C" [D] %d has taken the first fork 🍴 Fork: %d🍴\n"RST,
			elapsed, philo->id, philo->first_fork->fork_debug_id);
	else if (status == TAKE_SECOND_FORK)
		printf(W"%-6ld"M" [D] %d has taken the second fork 🍴 Fork: %d🍴\n"RST,
			elapsed, philo->id, philo->second_fork->fork_debug_id);
}

void	write_status(t_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	mutex_handler(&philo->table->write_mutex, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		fork_debug(status, philo, elapsed, debug);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(W"%-6ld"B" %d is eating\n"RST, elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(W"%-6ld"Y" %d is sleeping\n"RST, elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(W"%-6ld"G" %d is thinking\n"RST, elapsed, philo->id);
	else if (status == DIED)
		printf(W"%-6ld"RD" %d died\n"RST, elapsed, philo->id);
	mutex_handler(&philo->table->write_mutex, UNLOCK);
}
