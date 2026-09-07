/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

/**
 * Frees main fractal struct's malloc properties.
 * @param fractal Main fractal struct.
 */
int	close_lsr(const t_fractal *fractal)
{
	mlx_destroy_image(fractal->cxn, fractal->img.img_ptr);
	mlx_destroy_window(fractal->cxn, fractal->window);
	mlx_destroy_display(fractal->cxn);
	free(fractal->cxn);
	exit(EXIT_SUCCESS);
}

/**
 * Handles key presses for the fractal.
 *
 * Arrow keys shifts the fractal view,
 * Plus (or Numpad Plus) & Minus change iterations.
 * @param keysym X11 keysym code.
 * @param fractal Main fractal struct.
 */
int	key_lsr(const int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_lsr(fractal);
	if (keysym == XK_Left)
		fractal->shift_x -= 0.5 * fractal->zoom;
	else if (keysym == XK_Right)
		fractal->shift_x += 0.5 * fractal->zoom;
	else if (keysym == XK_Up)
		fractal->shift_y += 0.5 * fractal->zoom;
	else if (keysym == XK_Down)
		fractal->shift_y -= 0.5 * fractal->zoom;
	else if (keysym == XK_plus || keysym == XK_KP_Add)
		fractal->iterations += 10;
	else if (keysym == XK_minus)
		fractal->iterations -= 10;
	else
		return (0);
	fractal_render(fractal);
	return (0);
}

/**
 * Changes zoom based on mouse scroll wheel.
 * @param button X11 button code
 * @param x Required for hook, unused.
 * @param y Required for hook, unused.
 * @param fractal Main fractal struct.
 */
int	scroll_lsr(const int button, int x, int y, t_fractal *fractal)
{
	x = 0;
	y = 0;
	if (button == Button4)
		fractal->zoom *= 0.95;
	else if (button == Button5)
		fractal->zoom *= 1.05;
	else
		return (x);
	fractal_render(fractal);
	return (y);
}

/**
 * Updates the julia constant based on mouse position.
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 * @param fractal Main fractal struct.
 */
int	mouse_lsr(const int x, const int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		fractal->julia.real_num = scale(x, -2, +2,
				WIDTH) * fractal->zoom + fractal->shift_x;
		fractal->julia.i_num = scale(y, +2, -2,
				HEIGHT) * fractal->zoom + fractal->shift_y;
		fractal_render(fractal);
	}
	return (0);
}
