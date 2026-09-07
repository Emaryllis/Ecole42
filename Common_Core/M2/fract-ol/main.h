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
#ifndef MAIN_H
# define MAIN_H
# include <stdlib.h> // free
# include <unistd.h> // write
# include <X11/keysym.h>
# include <X11/X.h>
# include "minilibx-linux/mlx.h"

// Window size
# define WIDTH	800
# define HEIGHT	800

// Colors
# define BLACK  0x000000  // RGB(0, 0, 0)
# define WHITE  0xFFFFFF  // RGB(255, 255, 255)
# define PURPLE 0x660066  // RGB(102, 0, 102)

typedef struct s_complex
{
	double	real_num; // real number
	double	i_num; // imaginary number
}				t_complex;

typedef struct s_img
{
	void	*img_ptr; // mlx_new_image()
	char	*pixels; // mlx_get_data_addr()
	int		bpp; // bits per pixel, 32 for RGBA
	int		endian; // Required for init, unused.
	int		bytes_per_row;
}				t_img;

typedef struct s_fractal
{
	char		*name; // "mandelbrot" or "julia"
	void		*cxn; // mlx_init()
	void		*window; // mlx_new_window()
	t_img		img;
	double		mandel_escape; // (mandel's escape radius threshold)^2
	// image quality and rendering speed changes w value
	int			iterations;
	double		shift_x; // x offset based on user
	double		shift_y; // y offset based on user
	double		zoom; // zoom factor based on user
	t_complex	julia; // Used to set constant for Julia set
}				t_fractal;

// Str Utils
int			ft_strncmp(const char *s1, const char *s2, int n);
void		ft_putstr_fd(const char *s, const int fd);
double		ft_atodbl(const char *s);

// Math Utils
double		scale(double unscaled, double new_min, double new_max,
				double old_max);
t_complex	sum_complex(const t_complex z, const t_complex c);
t_complex	sq_complex(const t_complex z);

// Listeners
int			close_lsr(const t_fractal *fractal);
int			key_lsr(const int keysym, t_fractal *fractal);
int			scroll_lsr(int button, int x, int y, t_fractal *fractal);
int			mouse_lsr(const int x, const int y, t_fractal *fractal);

// Renders
void		init_fractal(t_fractal *fractal);
void		fractal_render(const t_fractal *fractal);
#endif