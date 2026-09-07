/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

/** Print error & exit w/ failure. */
static void	malloc_error(void)
{
	ft_putstr_fd("Malloc failed.\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/**
 * Init main fractal struct.
 * mandel_escape = (mandel's escape radius threshold)^2 = 2^2 = 4.
 * Random iteration start value.
 * Default values for shift_x, shift_y and zoom.
 */
static void	init_data(t_fractal *fractal)
{
	fractal->mandel_escape = 4;
	fractal->iterations = 42;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
}

/**
 * Initializes the keyboard, mouse scroll,
 * close window and mouse motion hooks.
 * @param fractal Main fractal struct.
 */
static void	init_hooks(t_fractal *fractal)
{
	mlx_hook(fractal->window, KeyPress, KeyPressMask,
		key_lsr, fractal);
	mlx_hook(fractal->window, ButtonPress, ButtonPressMask,
		scroll_lsr, fractal);
	mlx_hook(fractal->window, DestroyNotify, StructureNotifyMask,
		close_lsr, fractal);
	mlx_hook(fractal->window, MotionNotify, PointerMotionMask,
		mouse_lsr, fractal);
}

/**
 * Creates and initializes a new connection, window
 * and image for the fractal with malloc handling,
 * initializes the pixel ptr using the image ptr
 * for memory manipulation,
 * calls other initialization functions.
 * @param fractal Main fractal struct.
 */
void	init_fractal(t_fractal *fractal)
{
	fractal->cxn = mlx_init();
	if (fractal->cxn == NULL)
		malloc_error();
	fractal->window = mlx_new_window(fractal->cxn, WIDTH, HEIGHT,
			fractal->name);
	if (fractal->window == NULL)
	{
		mlx_destroy_display(fractal->cxn);
		free(fractal->cxn);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->cxn, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->cxn, fractal->window);
		mlx_destroy_display(fractal->cxn);
		free(fractal->cxn);
		malloc_error();
	}
	fractal->img.pixels = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.bytes_per_row,
			&fractal->img.endian);
	init_hooks(fractal);
	init_data(fractal);
}
