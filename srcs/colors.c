/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:58:58 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/01 10:07:26 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	add_shade(double distance, t_color color)
{
	int	col;

	col = (((int)color.r << 16) | ((int)color.g << 8) | ((int)color.b));
	return ((((int)(distance * 255)) << 24) | (col & 0x00FFFFFF));
}

int	color(int escape_time, int N_max)
{
	double t;
	t_color clr;

	t = (double)escape_time / (double)N_max;
	clr.t = 0;
	clr.r = 9 * (1 - t) * pow(t, 3) * 255;
	clr.g = 15 * pow((1 - t), 2) * pow(t, 2) * 255;
	clr.b = 8.5 * pow((1 - t), 3) * t * 255;
	return (((int)clr.r << 16) | ((int)clr.g << 8) | ((int)clr.b));
}

// int	main(void)
// {
// 	int		i;
// 	double	t;
// 	t_color	clr;

// 	i = -1;
// 	while (++i < 101)
// 	{
// 		t = (double) i / (double) 100;
// 		clr.r = 9 * (1 - t) * pow(t, 3) * 255;
// 		clr.g = 15 * pow((1 - t), 2) * pow(t, 2) * 255;
// 		clr.b = 8.5 * pow((1 - t), 3) * t * 255;
// 		printf("(%.2f) %#08x %3d %3d %3d\n", t, color(i, 100), clr.r, clr.g, clr.b);
// 	}
// }
