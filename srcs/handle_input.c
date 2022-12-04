/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:31:51 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/04 15:31:54 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	handle_no_event(void)
{
	return (0);
}

int	handle_key_input(int keysym, t_vars *vars)
{
	t_point	a;
	double	d;
	static int x;

	if (!vars || !(vars->win)  || !(vars->img) || !(vars->fractal.get_ev))
		return (-1);
	if (keysym == 53)
		free_all(vars->mlx, vars->window, vars->img, 1);
	d = (vars->img->max.re - vars->img->min.re) / 80;
	set_point(&a, 0, 0);
	if (keysym == 123)
		set_point(&a, -d, 0);
	else if (keysym == 124)
		set_point(&a, d, 0);
	else if (keysym == 125)
		set_point(&a, 0, -d);
	else if (keysym == 126)
		set_point(&a, 0, d);
	translate_img(vars->img, a, vars->fractal);
	fractal_to_img(vars->img, vars->fractal);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	fprintf(stderr, "(%d) synced (ks = %d)\n", ++x, keysym);
	return (0);
}

int	handle_mouse_input(int mousesym, int x, int y, t_vars *vars)
{
	t_point	a;
	t_point	max;
	t_point	min;
	double	zm;

	if (mousesym == 4 || mousesym == 5)
	{
		zm = (mousesym == 4) * 1 / 1.1 + (mousesym == 5) * 1.1;
		max = vars->img->max;
		min = vars->img->min;
		set_point(&a, min.re + x * (max.re - min.re) / vars->img->wid, \
			max.im - y * (max.im - min.im) / vars->img->hgt);
		zoom_point(vars->img, a, zm);
		set_fractal_ev(vars->img, vars->fractal, NULL);
		fractal_to_img(vars->img, vars->fractal);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	fprintf(stderr, "mouse = %d\n", mousesym);
	return (0);
}
