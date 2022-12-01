/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:10:13 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/30 16:12:42 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

t_point	*init_point(double re, double im)
{
	t_point	*z;

	z = malloc(sizeof(*z));
	if (!z)
		return (NULL);
	z->re = re;
	z->im = im;
	return (z);
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
