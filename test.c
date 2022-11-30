/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 05:12:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/30 07:05:06 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

typedef struct s_point
{
	double	re;
	double	im;
} t_point;

t_point	*init_point(double re, double im)
{
	t_point	*z;

	z = malloc(sizeof(*z));
	if (!z)
		return (NULL);
	z->re = re;
	z->im = im;
	return (z);
}

double	module(t_point *z)
{
	if (z == NULL)
		return (0);
	return (sqrt(pow(z->re, 2) + pow(z->im, 2)));
}

void	exit_points(t_point *a, t_point *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
	exit (-1);
}

void	*free_points(t_point *a, t_point *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
	return (NULL);
}

int	mandelbrot(double x, double y)
{
	int	iter;
	t_point	*z;
	t_point	*tmp;
	t_point	*c;

	z = init_point(0, 0);
	if (!z)
		exit_points(NULL, NULL);
	c = init_point(x, y);
	if (!c)
		exit_points(z, NULL);
	iter = -1;
	while (module(z) <= 2 && ++iter < 100)
	{
		tmp = init_point(z->re, z->im);
		if (!tmp)
			exit_points(z, c);
		z->re = pow(tmp->re, 2) - pow(tmp->im, 2) + c->re;
		z->im = 2 * tmp->re * tmp->im + c->im;
		free(tmp);
	}
	free_points(z, c);
	return (iter == 100);
}
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	int		length = 800;
	int		width = 800;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, width, length, "Hello world!");
	img.img = mlx_new_image(mlx, width, length);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	int i = -1;
	while (++i < width)
	{
		int	j = -1;
		while (++j < length)
		{
			double x = -2 + ((double)i) * 4 / width;
			double y = -2 + ((double)j) * 4 / width;
			if (mandelbrot(x, y))
				my_mlx_pixel_put(&img, i, j, 0);
			else
				my_mlx_pixel_put(&img, i, j, 1000000);
			if (x == 0 || y == 0)
				my_mlx_pixel_put(&img, i, j, 10000);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}