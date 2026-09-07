/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/05 17:51:01 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../main.h"

static void	thread_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == JOIN || code == DETACH))
		send_error("Thread value is invalid.\n");
	else if (status == EINVAL && code == CREATE)
		send_error("Invalid thread attributes.\n");
	else if (status == EAGAIN)
		send_error("Insufficient thread resources.\n");
	else if (status == ESRCH)
		send_error("Unable to find the thread specified.\n");
	else if (status == EPERM)
		send_error("The thread is not joinable.\n");
	else if (status == EDEADLK)
		send_error("Thread deadlock detected.\n");
	else
		send_error("Unknown thread error.\n");
}

void	thread_handler(pthread_t *thread, void *(*func)(void *), void *data,
			t_code code)
{
	if (code == CREATE)
		thread_error(pthread_create(thread, NULL, func, data), code);
	else if (code == JOIN)
		thread_error(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		thread_error(pthread_detach(*thread), code);
	else
		send_error("Wrong thread code.\n");
}

static void	mutex_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
		send_error("Mutex value is invalid.\n");
	else if (status == EINVAL && code == INIT)
		send_error("Mutex attributes are invalid.\n");
	else if (status == EBUSY)
		send_error("Mutex is locked.\n");
	else if (status == EDEADLK)
		send_error("Mutex deadlock detected.\n");
	else if (status == EPERM)
		send_error("Current thread does not own the mutex.\n");
	else if (status == ENOMEM)
		send_error("Malloc error on mutex initialization.\n");
	else
		send_error("Unknown mutex error.\n");
}

void	mutex_handler(t_mtx *mutex, t_code status)
{
	if (status == LOCK)
		mutex_error(pthread_mutex_lock(mutex), status);
	else if (status == UNLOCK)
		mutex_error(pthread_mutex_unlock(mutex), status);
	else if (status == INIT)
		mutex_error(pthread_mutex_init(mutex, NULL), status);
	else if (status == DESTROY)
		mutex_error(pthread_mutex_destroy(mutex), status);
	else
		send_error("Wrong mutex code.\n");
}
