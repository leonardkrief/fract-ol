/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:59:52 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/01 13:07:30 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	translate_img(t_image *img, t_point z)
{
	img->min.re += z.re;
	img->max.re += z.re;
	img->min.im += z.im;
	img->max.im += z.im;
}

void	zoom_img(t_image *img, t_point z, double t)
{
	int	min_re;
	int	min_im;
	int	max_re;
	int	max_im;

	min_re = img->min.re;
	min_im = img->min.im;
	max_re = img->max.re;
	max_im = img->max.im;
	img->min.re = z.re - (max_re - min_re) / (2 * t);
	img->max.re = z.re + (max_re - min_re) / (2 * t);
	img->min.im = z.im + (max_im - min_im) / (2 * t);
	img->max.im = z.im - (max_im - min_im) / (2 * t);
}

