/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fractals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 23:00:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/05 04:16:32 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	set_fractal_ev(t_image *img, t_fractal fractal, int *ev_tab)
{
	int		x;
	int		y;
	t_point	c;

	if (!img)
		return (-1);
	x = -1;
	while (++x < img->wid)
	{
		y = -1;
		while (++y < img->hgt)
		{
			c.re = (img->min.re + x * (img->max.re - img->min.re) / img->wid);
			c.im = (img->max.im - y * (img->max.im - img->min.im) / img->hgt);
			if (ev_tab)
				img->esc_val[y * img->wid + x] = fractal.get_ev(c, \
					fractal.param, fractal.n_max, ev_tab[y * img->wid + x]);
			else
				img->esc_val[y * img->wid + x] = fractal.get_ev(c, \
					fractal.param, fractal.n_max, 0);
		}
	}
	return (0);
}

int	fractal_to_img(t_image *img, t_fractal fractal)
{
	double		x;
	double		y;

	if (!img)
		return (-1);
	x = -1;
	while (++x < img->wid)
	{
		y = img->hgt;
		while (--y > -1)
			my_mlx_pixel_put(img, x, y, \
				color(img->esc_val[(int)y * img->wid + (int)x], fractal.n_max));
	}
	return (0);
}
