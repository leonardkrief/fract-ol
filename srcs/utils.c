/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:10:13 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/05 04:23:15 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	set_point(t_point *z, double re, double im)
{
	if (!z)
		return (-1);
	z->re = re;
	z->im = im;
	return (0);
}

int	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (!img)
		return (-1);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

int	zoom_point(t_image *img, t_point z, double t)
{
	double	min_re;
	double	min_im;
	double	max_re;
	double	max_im;

	if (!img || t == 0)
		return (-1);
	min_re = img->min.re;
	min_im = img->min.im;
	max_re = img->max.re;
	max_im = img->max.im;
	img->min.re = ((t - 1) * z.re + min_re) / t;
	img->max.re = ((t - 1) * z.re + max_re) / t;
	img->min.im = ((t - 1) * z.im + min_im) / t;
	img->max.im = ((t - 1) * z.im + max_im) / t;
	return (0);
}

int	add_shade(double distance, t_color color)
{
	int	col;

	col = (((int)color.r << 16) | ((int)color.g << 8) | ((int)color.b));
	return ((((int)(distance * 255)) << 24) | (col & 0x00FFFFFF));
}

int	color(int escape_time, int N_max)
{
	double	t;
	t_color	clr;

	t = (double)escape_time / (double)N_max;
	clr.t = 0;
	clr.r = 9 * (1 - t) * pow(t, 3) * 255;
	clr.g = 15 * pow((1 - t), 2) * pow(t, 2) * 255;
	clr.b = 8.5 * pow((1 - t), 3) * t * 255;
	return (((int)clr.r << 16) | ((int)clr.g << 8) | ((int)clr.b));
}

int	ft_putstr_fd(int fd, char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (-1);
	while (str[len])
		len++;
	write(fd, str, len);
	return (len);
}

int	ft_putstr(char *str)
{
	int	len;

	len = ft_putstr_fd(STDOUT_FILENO, str);
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	else
		return (((unsigned char) s1[i]) - ((unsigned char) s2[i]));
}
