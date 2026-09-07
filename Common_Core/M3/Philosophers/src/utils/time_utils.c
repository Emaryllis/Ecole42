/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/07 16:19:05 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../main.h"

long	get_time(t_timecode time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (send_error("Failed to get time of day."));
	if (time_code == SECOND)
		return (tv.tv_sec);
	else if (time_code == MILLISECOND)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (time_code == MICROSECOND)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	return (send_error("Wrong time code."));
}

void	btr_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}
