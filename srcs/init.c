/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:59:13 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/04 15:29:40 by lkrief           ###   ########.fr       */
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
	win->win = mlx_new_window(win->mlx, wid, hgt, "fract-ol");
	if (win->win == NULL)
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
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), \
					&(img->line_length), &(img->endian));
	img->wid = wid;
	img->hgt = hgt;
	img->esc_val = malloc(sizeof(*(img->esc_val)) * img->wid * img->hgt);
	if (img->esc_val == NULL)
	{
		mlx_destroy_image(img->mlx, img->img);
		free(img);
		return (NULL);
	}
	set_point(&(img->min), -2, -2 * (double)hgt/(double)wid);
	set_point(&(img->max), 2, 2 * (double)hgt/(double)wid);
	return (img);
}

int	init_fractal(t_fractal *fractal, int N_max, \
	int (*f)(t_point, t_point, int, int), t_point param)
{
	fractal->N_max = N_max;
	fractal->get_ev = f;
	fractal->param = param;
	return (0);
}

int	init_wo_fractal(t_vars *vars, void **mlx, t_window **win, t_image **img)
{
	*mlx = mlx_init();
	if (*mlx == NULL)
		exit (-1);
	*win = init_window(*mlx, WIDTH, HEIGHT);
	if (!(*win))
		return (free_all(*mlx, NULL, NULL, -1));
	*img = init_image(*mlx, WIDTH, HEIGHT);
	if (!(*img))
		return(free_all(*mlx, *win, NULL, -1));
	vars->mlx = *mlx;
	vars->win = (*win)->win;
	vars->window = *win;
	vars->img = *img;
	return (0);
}
