/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/05 17:02:50 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static long	ft_atol(const char *str)
{
	int		len;
	long	num;

	num = 0;
	len = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (send_error("Negative numbers are not allowed."));
	if (*str < '0' || *str > '9')
		return (send_error("Invalid character found."));
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str++ - '0');
		len++;
	}
	if (len > 10 || num > INT_MAX)
		return (send_error("Number too large."));
	return (num);
}

// Time converted from milliseconds to microseconds
void	parse_inputs(t_table *table, char **v)
{
	table->philo_nbr = ft_atol(v[1]);
	table->time_to_die = ft_atol(v[2]) * 1e3;
	table->time_to_eat = ft_atol(v[3]) * 1e3;
	table->time_to_sleep = ft_atol(v[4]) * 1e3;
	if (table->philo_nbr == -1 || table->time_to_die == -1
		|| table->time_to_eat == -1 || table->time_to_sleep == -1)
	{
		table->philo_nbr = -1;
		table->error = true;
		return ;
	}
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
	{
		send_error("Time values must be at least 60ms.");
		table->philo_nbr = -1;
		table->error = true;
		return ;
	}
	if (v[5])
		table->nbr_limit_meals = ft_atol(v[5]);
	else
		table->nbr_limit_meals = -1;
}
