/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

/**
 * Initializes the main fractal struct with
 * argv values if either mandelbrot or julia.
 * Delegates the logic to helper functions.
 * Exits as failure with usage message if
 * the arguments are invalid.
 */
int	main(const int argc, char **argv)
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		fractal.name = argv[1];
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia.real_num = ft_atodbl(argv[2]);
			fractal.julia.i_num = ft_atodbl(argv[3]);
		}
		init_fractal(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.cxn);
	}
	else
	{
		ft_putstr_fd(
			"Usage:\n- ./fractol mandelbrot\n- ./fractol julia <real> <i>\n",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
