/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:50:07 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/05 04:28:33 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	translate_img_1(t_image *img, t_point z, t_fractal fractal)
{
	int		x;
	int		i;
	int		j;
	t_point	c;

	x = fabs(z.re) / (img->max.re - img->min.re) * img->wid;
	set_point(&(img->min), img->min.re + z.re, img->min.im + z.im);
	set_point(&(img->max), img->max.re + z.re, img->max.im + z.im);
	i = -1;
	while (++i < img->wid && z.re > 0 && z.im == 0)
	{
		j = -1;
		while (++j < img->hgt)
		{
			c.re = (img->min.re + i * (img->max.re - img->min.re) / img->wid);
			c.im = (img->max.im - j * (img->max.im - img->min.im) / img->hgt);
			if (i < img->wid - x)
				img->esc_val[j * img->wid + i] = \
					img->esc_val[j * img->wid + (i + x)];
			else
				img->esc_val[j * img->wid + i] = \
					fractal.get_ev(c, fractal.param, fractal.n_max, 0);
		}
	}
}

void	translate_img_2(t_image *img, t_point z, t_fractal fractal)
{
	int		y;
	int		i;
	int		j;
	t_point	c;

	y = fabs(z.im) / (img->max.im - img->min.im) * img->hgt;
	set_point(&(img->min), img->min.re + z.re, img->min.im + z.im);
	set_point(&(img->max), img->max.re + z.re, img->max.im + z.im);
	i = -1;
	while (++i < img->wid && z.re == 0 && z.im < 0)
	{
		j = -1;
		while (++j < img->hgt)
		{
			c.re = (img->min.re + i * (img->max.re - img->min.re) / img->wid);
			c.im = (img->max.im - j * (img->max.im - img->min.im) / img->hgt);
			if (j < img->hgt - y)
				img->esc_val[j * img->wid + i] = \
					img->esc_val[(j + y) * img->wid + i];
			else
				img->esc_val[j * img->wid + i] = \
					fractal.get_ev(c, fractal.param, fractal.n_max, 0);
		}
	}
}

void	translate_img_3(t_image *img, t_point z, t_fractal fractal)
{
	int		x;
	int		i;
	int		j;
	t_point	c;

	x = fabs(z.re) / (img->max.re - img->min.re) * img->wid;
	set_point(&(img->min), img->min.re + z.re, img->min.im + z.im);
	set_point(&(img->max), img->max.re + z.re, img->max.im + z.im);
	i = img->wid;
	while (--i >= 0 && z.re < 0 && z.im == 0)
	{
		j = img->hgt;
		while (--j >= 0)
		{
			c.re = (img->min.re + i * (img->max.re - img->min.re) / img->wid);
			c.im = (img->max.im - j * (img->max.im - img->min.im) / img->hgt);
			if (i > x)
				img->esc_val[j * img->wid + i] = \
					img->esc_val[j * img->wid + (i - x)];
			else
				img->esc_val[j * img->wid + i] = \
					fractal.get_ev(c, fractal.param, fractal.n_max, 0);
		}
	}
}

void	translate_img_4(t_image *img, t_point z, t_fractal fractal)
{
	int		y;
	int		i;
	int		j;
	t_point	c;

	y = fabs(z.im) / (img->max.im - img->min.im) * img->hgt;
	set_point(&(img->min), img->min.re + z.re, img->min.im + z.im);
	set_point(&(img->max), img->max.re + z.re, img->max.im + z.im);
	i = img->wid;
	while (--i >= 0 && z.re == 0 && z.im > 0)
	{
		j = img->hgt;
		while (--j >= 0)
		{
			c.re = (img->min.re + i * (img->max.re - img->min.re) / img->wid);
			c.im = (img->max.im - j * (img->max.im - img->min.im) / img->hgt);
			if (j > y)
				img->esc_val[j * img->wid + i] = \
					img->esc_val[(j - y) * img->wid + i];
			else
				img->esc_val[j * img->wid + i] = \
					fractal.get_ev(c, fractal.param, fractal.n_max, 0);
		}
	}
}

int	translate_img(t_image *img, t_point z, t_fractal fractal)
{
	if (!img)
		return (-1);
	if (z.re > 0 && z.im == 0)
		translate_img_1(img, z, fractal);
	else if (z.re == 0 && z.im < 0)
		translate_img_2(img, z, fractal);
	else if (z.re < 0 && z.im == 0)
		translate_img_3(img, z, fractal);
	else if (z.re == 0 && z.im > 0)
		translate_img_4(img, z, fractal);
	return (0);
}
