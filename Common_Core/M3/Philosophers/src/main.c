/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/05 16:06:30 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	if (table->philo_nbr < 0)
		return ;
	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		mutex_handler(&philo->philo_mutex, DESTROY);
	}
	mutex_handler(&table->table_mutex, DESTROY);
	mutex_handler(&table->write_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

static void	print_error(t_table *table, const char *msg)
{
	if (!table->error && DEBUG)
		printf(G"✅ %s successful\n"RST, msg);
	else if (DEBUG)
		printf(RD"❌ %s failed\n"RST, msg);
}

int	main(int c, char **v)
{
	t_table	table;

	if (c != 5 && c != 6)
		return (send_error("Wrong number of arguments."));
	table.error = false;
	parse_inputs(&table, v);
	print_error(&table, "Parsing");
	if (!table.error)
		data_init(&table);
	print_error(&table, "Initialization");
	if (!table.error)
		start_dinner(&table);
	print_error(&table, "Dinner");
	clean(&table);
	print_error(&table, "Cleanup");
	return (EXIT_SUCCESS);
}
