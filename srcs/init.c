/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:59:13 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/01 12:55:25 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_window	*init_window(void *mlx, int wid, int hgt)
{
	t_window	*win;

	win = malloc(sizeof(*win));
	if (!win)
		return (NULL);
	win->mlx = mlx;
	win->mlx_win = mlx_new_window(win->mlx, wid, hgt, "fract-ol");
	if (win->mlx_win == NULL)
	{
		free(win);
		return (NULL);
	}
	win->wid = wid;
	win->hgt = hgt;
	return (win);
}

t_image	*init_image(void *mlx, int wid, int hgt)
{
	t_image	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return(NULL);
	img->mlx = mlx;
	img->img = mlx_new_image(mlx, wid, hgt);
	if (img->img == NULL)
	{
		free(img);
		return (NULL);
	}
	img->esc_val = malloc(sizeof(*(img->esc_val)) * img->wid * img->hgt);
	if (img->esc_val == NULL)
	{
		mlx_destroy_image(img->mlx, img->img);
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), \
					&(img->line_length), &(img->endian));
	img->wid = wid;
	img->hgt = hgt;
	set_point(&(img->min), -2, -2);
	set_point(&(img->max), 2, 2);
	return (img);
}
