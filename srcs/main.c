/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 05:12:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/03 10:56:55 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
#include <unistd.h>

int	handle_no_event(void)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	handle_key_input(int keysym, t_vars *vars)
{
	t_point	a;
	double	d;
	static int x;

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
		set_fractal_ev(vars->img, vars->fractal, NULL, 0);
		fractal_to_img(vars->img, vars->fractal);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	fprintf(stderr, "mouse = %d\n", mousesym);
	return (0);
}

int	main(void)
{
	t_window	*win;
	t_image		*img;
	t_fractal	fractal;
	t_point z;
	t_vars vars;
	int			wid;
	int			hgt;
	void	*mlx;

//fractal init
	fractal.N_max = 50;
	fractal.get_ev = *mandelbrot;

//mlx init
	mlx = mlx_init();
	if (mlx == NULL)
		return (-1);

//win init
	wid = 500;
	hgt = 500;
	win = init_window(mlx, wid, hgt);
	if (!win)
		return (-1);

//img init
	img = init_image(mlx, wid, hgt);
	if (!img)
		return(-1); // il faudra free le window

//vars init
	vars.mlx = mlx;
	vars.win = win->win;
	vars.img = img;
	vars.fractal = fractal;

// first image
	set_point(&z, 0.5, -0.5);
	//zoom_point(img, z, 1);
	set_fractal_ev(img, fractal, NULL, 0);
	fractal_to_img(img, fractal);
	put_grid(img, 0x000000ff);
	mlx_put_image_to_window(mlx, win->win, img->img, 0, 0);

// loops
	//mlx_loop_hook(vars.mlx, &handle_no_event, &vars);
	mlx_key_hook(win->win, &handle_key_input, &vars);
	mlx_mouse_hook(win->win, &handle_mouse_input, &vars);
	mlx_loop(win->mlx);

	free(mlx);
	return (0);
}
