/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:59:52 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/02 04:57:43 by lkrief           ###   ########.fr       */
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
	img->min.re += z.re;
	img->max.re += z.re;
	img->min.im += z.im;
	img->max.im += z.im;
	i = (z.re <= 0 ? 0 : fmax(0, img->wid - x)) - 1;
	while (++i < (z.re <= 0 ? x : img->wid))
	{
		j = (z.im <= 0 ? fmax(0, img->hgt - y) : 0) - 1;
		while (++j < (z.im <= 0 ? img->hgt : x))
		{
			c.re = (img->min.re + i * (img->max.re - img->min.re) / img->wid);
			c.im = (img->max.im - j * (img->max.im - img->min.im) / img->hgt);
			img->esc_val[j * img->wid + i] = fractal.get_ev(c, fractal.N_max, 0);
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
			if (x % (img->wid / 10) == 0 || (y + 1) % (img->hgt / 10) == 0)
				my_mlx_pixel_put(img, x, y, colr);
		}
	}
}

// z est la position de la souris dans l'ecran referencée suivant les pixels
void	zoom_img(t_image *img, t_point z, double t)
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
	img->min.im = z.im + (max_im - min_im) / (2 * t);
	img->max.im = z.im - (max_im - min_im) / (2 * t);
}

