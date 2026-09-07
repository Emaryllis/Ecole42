/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

/**
 * Offsets
 * @param x Pixel x coords
 * @param y Pixel y coords
 * @param img Main image struct
 * @param color Pixel color
 */
static void	put_pixel(const int x, const int y, const t_img *img, int color)
{
	const int	offset = y * img->bytes_per_row + x * (img->bpp / 8);

	*(unsigned int *)(img->pixels + offset) = color;
}

/**
 * For the Julia set, assigns argv values to c.
 * For the Mandelbrot set, assigns c to the scaled z.
 *
 * @param z        Current pixel's complex coordinate.
 * @param c        Complex constant to be initialized.
 * @param fractal  Main fractal struct.
 */

static void	init_complex(t_complex *z, t_complex *c, const t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->real_num = fractal->julia.real_num;
		c->i_num = fractal->julia.i_num;
	}
	else
	{
		c->real_num = z->real_num;
		c->i_num = z->i_num;
	}
}

/**
 * Initializes z to the scaled pixel coords,
 * defines c based on fractal type, then sets
 * z and c based on the fractal iterations, and
 * colors the pixel white.
 * If the magnitude of z at any point exceeds
 * the escape radius (calculated using pythagorean
 * theorem), it colors the pixel with a psychedelic
 * color.
 *
 * @param x pixel x coords
 * @param y pixel y coords
 * @param fractal main fractal struct
 */
static void	pixel_handler(const int x, const int y, const t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = -1;
	z.real_num = scale(x, -2, +2, WIDTH)
		* fractal->zoom + fractal->shift_x;
	z.i_num = scale(y, +2, -2, HEIGHT)
		* fractal->zoom + fractal->shift_y;
	init_complex(&z, &c, fractal);
	while (fractal->iterations > ++i)
	{
		z = sum_complex(sq_complex(z), c);
		if (z.real_num * z.real_num + z.i_num * z.i_num
			> fractal->mandel_escape)
		{
			color = scale(i, BLACK, WHITE,
					fractal->iterations);
			put_pixel(x, y, &fractal->img, color);
			return ;
		}
	}
	put_pixel(x, y, &fractal->img, PURPLE);
}

void	fractal_render(const t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			pixel_handler(x, y, fractal);
	}
	mlx_put_image_to_window(fractal->cxn, fractal->window,
		fractal->img.img_ptr, 0, 0);
}
