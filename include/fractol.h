/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:08:50 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/02 18:55:48 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>

typedef struct s_point
{
	double	re;
	double	im;
}	t_point;

typedef struct s_color
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_window {
	void	*mlx;
	void	*mlx_win;
	int		hgt;
	int		wid;
}	t_window;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	int		wid;
	int		hgt;
	int		*esc_val;
	t_point	min;
	t_point	max;
}	t_image;

typedef struct s_fractal {
	int	N_max;
	int (*get_ev)(t_point, int, int);
}	t_fractal;

// colors.c
int	add_shade(double distance, t_color color);
int	color(int escape_time, int N_max);

// init.c
t_window	*init_window(void *mlx, int wid, int hgt);
t_image		*init_image(void *mlx, int wid, int hgt);

// mandelbrot.c
int		mandelbrot(t_point c, int N_max, int n);
void	set_fractal_ev(t_image *img, t_fractal fractal, int *ev_tab, int bool);
void	fractal_to_img(t_image *img, t_fractal fractal);

// display.c
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	translate_img(t_image *img, t_point z, t_fractal fractal);
void	zoom_mouse(t_image *img, t_point mouse, double t);
void	zoom_point(t_image *img, t_point z, double t);
void	put_grid(t_image *img, int colr);

// points.c
void	set_point(t_point *z, double re, double im);
double	module_point(t_point z);
void	exit_points(t_point *a, t_point *b);
void			*free_points(t_point *a, t_point *b);

#endif
