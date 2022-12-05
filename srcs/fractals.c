/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:48:20 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/05 04:25:00 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	mandelbrot(t_point c, t_point param, int N_max, int n)
{
	double	q;
	t_point	z;
	t_point	tmp;

	set_point(&z, 0, 0 * param.re);
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

int	julia(t_point z, t_point c, int N_max, int n)
{
	double static	r;
	double			delta;
	double			cap;
	t_point			tmp;

	if (sqrt(pow(c.re, 2) + pow(c.im, 2)) > r * (r - 1))
	{
		delta = 1 + 4 * sqrt(pow(c.re, 2) + pow(c.im, 2));
		r = pow ((1 - sqrt(delta)) / 2, 2);
		if (r * (r - 1) < 0)
			r = pow ((1 + sqrt(delta)) / 2, 2);
	}
	set_point(&z, pow(z.re, 2) - pow(z.im, 2) + c.re, 2 * z.re * z.im + c.im);
	cap = r * (r - 1);
	while (pow(z.re, 2) + pow(z.im, 2) <= cap && (++n < N_max))
	{
		tmp.re = z.re;
		tmp.im = z.im;
		z.re = pow(tmp.re, 2) - pow(tmp.im, 2) + c.re;
		z.im = 2 * tmp.re * tmp.im + c.im;
	}
	return (n);
}

int	tricorn(t_point c, t_point param, int N_max, int n)
{
	t_point	z;
	t_point	tmp;

	set_point(&z, 0, 0 * param.re);
	while (pow(z.re, 2) + pow(z.im, 2) <= 4 && (++n < N_max))
	{
		tmp.re = z.re;
		tmp.im = -z.im;
		z.re = pow(tmp.re, 2) - pow(tmp.im, 2) + c.re;
		z.im = 2 * tmp.re * tmp.im + c.im;
	}
	return (n);
}

int	lifetree(t_point z, t_point c, int N_max, int n)
{
	double	ep;
	double	mdl;
	double	tht;

	ep = 1.5;
	while (pow(z.re, 2) + pow(z.im, 2) <= 4 && (++n < N_max))
	{
		mdl = pow(sqrt(z.re * z.re + z.im * z.im), ep);
		tht = atan(z.im / z.re);
		set_point(&z, mdl * cos(ep * tht) + c.re, mdl * sin(ep * tht) + c.im);
	}
	return (n);
}

int	mandeltrig(t_point c, t_point param, int N_max, int n)
{
	t_point	z;
	t_point	tmp;

	set_point(&z, 0, 0 * param.re);
	while (pow(z.re, 2) + pow(z.im, 2) <= 4 && (++n < N_max))
	{
		tmp.re = z.re;
		tmp.im = z.im;
		z.re = tan(pow(tmp.re, 2) - pow(tmp.im, 2) + c.re);
		z.im = 2 * tmp.re * tmp.im + c.im;
		z.im = cos(z.im) + sin(z.im);
	}
	return (n);
}
