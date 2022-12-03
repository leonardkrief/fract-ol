/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 05:12:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/03 07:16:56 by lkrief           ###   ########.fr       */
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
	static int x;

	set_point(&a, 0.1, 0);
	if (keysym == 123) // LEFT
		set_point(&a, -0.01, 0);
	if (keysym == 124) // RIGHT
		set_point(&a, 0.01, 0);
	if (keysym == 125) // DOWN
		set_point(&a, 0, -0.01);
	if (keysym == 126) // UP
		set_point(&a, 0, 0.01);
	translate_img(vars->img, a, vars->fractal);
	//set_fractal_ev(vars->img, vars->fractal, NULL, 0);
	fractal_to_img(vars->img, vars->fractal);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);

	fprintf(stderr, "(%d) synced (ks = %d)\n", ++x, keysym);
	return (0);
}

int	handle_mouse_input(int mousesym, int x, int y, t_vars *vars)
{
	t_point	a;
	static int p;

	++p;
	//mlx_mouse_get_pos(vars->win, &x, &y);
	if (x && y)
		a.re = 0;
	set_point(&a, -0.7497065, 0.0314565);
	vars->fractal.N_max += 10;
	zoom_point(vars->img, a, 1.1);
	set_fractal_ev(vars->img, vars->fractal, NULL, 0);
	fractal_to_img(vars->img, vars->fractal);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	//mlx_get_screen_size(vars->mlx, &(a.re), &(a.im));
	fprintf(stderr, "(%d) synced (mouse = %d)\n", ++p, mousesym);
	fprintf(stderr, "           %.2f\n    %.2f        %.2f\n           %.2f\n", vars->img->min.im, vars->img->min.re, vars->img->max.re, vars->img->max.im);
	fprintf(stderr, "     N_max = %d, zoom = %.2f", vars->fractal.N_max, pow(1.1, p));
	//fprintf(stderr, "screen size %.4f %.4f", a.re, a.im);
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
	fractal.N_max = 500;
	fractal.get_ev = *mandelbrot;

//mlx init
	mlx = mlx_init();
	if (mlx == NULL)
		return (-1);
	mlx_do_key_autorepeaton(mlx);

//win init
	wid = 1280;
	hgt = 800;
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
