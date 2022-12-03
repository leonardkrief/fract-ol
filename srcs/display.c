/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:59:52 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/03 00:12:34 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	translate_img(t_image *img, t_point z, t_fractal fractal)
{
	int	x;
	int	y;
	int	i;
	int	j;
	t_point c;

	x = fabs(z.re) / (img->max.re - img->min.re) * img->wid;
	y = fabs(z.im) / (img->max.im - img->min.im) * img->hgt;
	set_point(&(img->min), img->min.re + z.re, img->min.im + z.im);
	set_point(&(img->max), img->max.re + z.re, img->max.im + z.im);
	i = -1;
	while (++i < img->wid)
	{
		j = -1;
		while (++j < img->hgt)
		{
			c.re = (img->min.re + i * (img->max.re - img->min.re) / img->wid);
			c.im = (img->max.im - j * (img->max.im - img->min.im) / img->hgt);
			if (z.re >= 0 && z.im >= 0)
			{
				if (i < (img->wid - x) && j > y)
					img->esc_val[j * img->wid + i] = img->esc_val[(j - y) * img->wid + (i + x)];
				else
					img->esc_val[j * img->wid + i] = fractal.get_ev(c, fractal.N_max, 0);
			}
			else if (z.re >= 0 && z.im < 0)
			{
				if (i < (img->wid - x) && j < img->hgt - y)
					img->esc_val[j * img->wid + i] = img->esc_val[(j + y) * img->wid + (i + x)];
				else
					img->esc_val[j * img->wid + i] = fractal.get_ev(c, fractal.N_max, 0);
			}
			else if (z.re < 0 && z.im >= 0)
			{
				if (i > x && j > y)
					img->esc_val[j * img->wid + i] = img->esc_val[(j - y) * img->wid + (i - x)];
				else
					img->esc_val[j * img->wid + i] = fractal.get_ev(c, fractal.N_max, 0);
			}
			else if (z.re < 0 && z.im < 0)
			{
				if (i > x && j < img->hgt - y)
					img->esc_val[j * img->wid + i] = img->esc_val[(j + y) * img->wid + (i - x)];
				else
					img->esc_val[j * img->wid + i] = fractal.get_ev(c, fractal.N_max, 0);
			}
		}
	}
}

void	put_grid(t_image *img, int colr)
{
	int		x;
	int		y;

	x = -1;
	while (++x < img->wid)
	{
		y = img->hgt;
		while (--y > -1)
		{
			if (fabs(img->min.re + x * (img->max.re - img->min.re) / img->wid) <= 0.001
				|| fabs(img->max.im - y * (img->max.im - img->min.im) / img->hgt) <= 0.001)
				my_mlx_pixel_put(img, x, y, colr);
		}
	}
}

// on zoom en centrant sur un point, pas tres malin, mieux zoomer sur la
// position de la souris
void	zoom_mouse(t_image *img, t_point mouse, double t)
{
	int		min_re;
	int		min_im;
	int		max_re;
	int		max_im;
	t_point	z;

	if (t == 0)
		return ;
	min_re = img->min.re;
	min_im = img->min.im;
	max_re = img->max.re;
	max_im = img->max.im;
	z.re = mouse.re / img->wid * (max_re - min_re);
	z.im = mouse.im / img->hgt * (max_im - min_im);
	img->min.re = z.re - (max_re - min_re) / (2 * t);
	img->max.re = z.re + (max_re - min_re) / (2 * t);
	img->min.im = z.im + (max_im - min_im) / (2 * t);
	img->max.im = z.im - (max_im - min_im) / (2 * t);
}

void	zoom_point(t_image *img, t_point z, double t)
{
	int	min_re;
	int	min_im;
	int	max_re;
	int	max_im;

	if (t == 0)
		return ;
	min_re = img->min.re;
	min_im = img->min.im;
	max_re = img->max.re;
	max_im = img->max.im;
	img->min.re = z.re - (max_re - min_re) / (2 * t);
	img->max.re = z.re + (max_re - min_re) / (2 * t);
	img->min.im = z.im - (max_im - min_im) / (2 * t);
	img->max.im = z.im + (max_im - min_im) / (2 * t);
}
