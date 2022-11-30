/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:08:50 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/30 16:13:05 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>

typedef struct	s_window {
	void	*mlx;
	void	*mlx_win;
	int		len;
	int		wid;
} t_window;

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_image;

typedef struct s_point
{
	double	re;
	double	im;
} t_point;

// init.c
t_window *init_window(int wid, int len);
t_image *init_image(t_window *win, int wid, int len);

// mandelbrot.c
int	mandelbrot_radius(t_point *c, int precision);
void	mandelbrot_to_win(t_window *win, t_image *img);

// pixels.c
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);

// points.c
t_point	*init_point(double re, double im);
double	module_point(t_point *z);
void	exit_points(t_point *a, t_point *b);
void	*free_points(t_point *a, t_point *b);

#endif
