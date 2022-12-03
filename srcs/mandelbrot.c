/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 23:00:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/02 23:38:03 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	mandelbrot(t_point c, int N_max, int n)
{
	double	q;
	t_point	z;
	t_point	tmp;

	set_point(&z, 0, 0);
	q = pow(c.re - 0.25, 2) + pow(c.im, 2);
	if (q * (q + c.re - 0.25) < pow(c.im, 2) * 0.25
		|| pow(1 + c.re, 2) + pow(c.im, 2) < 0.0625)
		return (N_max);
	while (pow(z.re, 2) + pow(z.im, 2) <= 4 && (++n < N_max))
	{
		tmp.re = z.re;
		tmp.im = z.im;
		z.re = pow(tmp.re, 2) - pow(tmp.im, 2) + c.re;
		z.im = 2 * tmp.re * tmp.im + c.im;
	}
	return (n);
}

void	set_fractal_ev(t_image *img, t_fractal fractal, int *ev_tab, int bool)
{
	int		x;
	int		y;
	t_point	c;

	x = -1;
	while (++x < img->wid)
	{
		y = -1;
		while (++y < img->hgt)
		{
			c.re = (img->min.re + x * (img->max.re - img->min.re) / img->wid);
			c.im = (img->max.im - y * (img->max.im - img->min.im) / img->hgt);
			if (bool)
				img->esc_val[y * img->wid + x] = fractal.get_ev(c, \
					fractal.N_max, ev_tab[y * img->wid + x]);
			else
				img->esc_val[y * img->wid + x] = fractal.get_ev(c, \
					fractal.N_max, 0);
		}
	}
}

void	fractal_to_img(t_image *img, t_fractal fractal)
{
	double		x;
	double		y;

	x = -1;
	while (++x < img->wid)
	{
		y = img->hgt;
		while (--y > -1)
			my_mlx_pixel_put(img, x, y, \
				color(img->esc_val[(int)y * img->wid + (int)x], fractal.N_max));
	}
}
