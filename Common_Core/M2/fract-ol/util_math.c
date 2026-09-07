/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

/**
 * Scales using this formula:
 * (maxAllowed - minAllowed) * (unscaledNum - min) / (max - min) + minAllowed
 * Treats the old min as 0 since for this use case it will always be 0.
 */
double	scale(double unscaled, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (unscaled - 0) / (old_max - 0) + new_min);
}

/** Basic addition */
t_complex	sum_complex(const t_complex z, const t_complex c)
{
	t_complex	result;

	result.real_num = z.real_num + c.real_num;
	result.i_num = z.i_num + c.i_num;
	return (result);
}

/**
 * Squares a complex number by the formula:
 * (real + i)^2 = (real^2 - i^2) + 2*real*i
 */
t_complex	sq_complex(const t_complex z)
{
	t_complex	result;

	result.real_num = z.real_num * z.real_num - z.i_num * z.i_num;
	result.i_num = 2 * z.real_num * z.i_num;
	return (result);
}
