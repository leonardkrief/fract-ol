/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 23:00:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/30 23:00:07 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

int	mandelbrot_escape_time(t_point c, int N_max)
{
	int		n;
	t_point	z;
	t_point	tmp;

	n = 0;
	z.re = 0;
	z.im = 0;
	while (pow(z.re, 2) + pow(z.im, 2) <= 4 && (++n < N_max))
	{
		tmp.re = z.re;
		tmp.im = z.im;
		z.re = pow(tmp.re, 2) - pow(tmp.im, 2) + c.re;
		z.im = 2 * tmp.re * tmp.im + c.im;
	}
	return (n);
}

void	mandelbrot_to_win(t_window *win, t_image *img, int N_max)
{
	int		i;
	int		j;
	int		col;
	t_point	c;

	i = -1;
	while (++i < img->wid)
	{
		j = -1;
		while (++j < img->len)
		{
			c.re = (-1 + (double)i * 2 / img->wid) * img->zoom + img->center.re;
			c.im = (-1 + (double)j * 2 / img->len) * img->zoom - img->center.im;
			col = color(mandelbrot_escape_time(c, N_max), N_max);
			my_mlx_pixel_put(img, i, j, col);
		}
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, img->img, 0, 0);
	mlx_loop(win->mlx);
}
