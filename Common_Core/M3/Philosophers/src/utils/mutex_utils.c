/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/05 18:29:03 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../main.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

void	increase_long(t_mtx *mutex, long *value)
{
	mutex_handler(mutex, LOCK);
	(*value)++;
	mutex_handler(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, const long *value)
{
	long	ret;

	set_long(mutex, &ret, *value);
	return (ret);
}

bool	get_bool(t_mtx *mutex, const bool *value)
{
	bool	ret;

	set_bool(mutex, &ret, *value);
	return (ret);
}
