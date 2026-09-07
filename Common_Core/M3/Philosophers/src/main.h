/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/05 16:12:18 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define RST "\033[0m"
# define RD "\033[0;31m"
# define G "\033[0;32m"
# define Y "\033[0;33m"
# define B "\033[0;34m"
# define M "\033[0;35m"
# define C "\033[0;36m"
# define W "\033[0;37m"

# define DEBUG false

// Aliases for data types
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

// Enums
typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_code;

typedef enum e_timecode
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_timecode;

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}	t_status;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_debug_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	t_fork		*first_fork;
	t_fork		*second_fork;
	long		last_meal_time;
	int			meals_counter;
	bool		full;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}				t_philo;

struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		threads_running_nbr;
	long		start_simulation;
	bool		end_simulation;
	bool		threads_ready;
	bool		error;
	pthread_t	monitor_id;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
};

// Utils
int		send_error(const char *error);
void	*btr_malloc(size_t size);
bool	simulation_finished(t_table *table);

// Display Utils
void	write_status(t_status status, t_philo *philo, bool debug);

// Time Utils
long	get_time(t_timecode time_code);
void	btr_usleep(long usec, t_table *table);

// Thread & Mutex utils
void	mutex_handler(t_mtx *mutex, t_code status);
void	thread_handler(pthread_t *thread, void *(*func)(void *), void *data,
			t_code code);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
void	set_long(t_mtx *mutex, long *dest, long value);
void	increase_long(t_mtx *mutex, long *value);
long	get_long(t_mtx *mutex, const long *value);
bool	get_bool(t_mtx *mutex, const bool *value);

// Synchronization utils
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, const long *threads, long philo_nbr);
void	desync_philos(t_philo *philo, void (*thinking)(t_philo *, bool));

// Main functions
void	parse_inputs(t_table *table, char **v);
void	data_init(t_table *table);
void	start_dinner(t_table *table);
void	*monitor(void *data);
#endif
