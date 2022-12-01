/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:10:13 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/01 12:16:39 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	set_point(t_point *z, double re, double im)
{
	z->re = re;
	z->im = im;
}

double	module_point(t_point z)
{
	return (sqrt(pow(z.re, 2) + pow(z.im, 2)));
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
