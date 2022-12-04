/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 05:12:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/04 04:21:23 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	fractol(t_args *args)
{
	void		*mlx;
	t_window	*win;
	t_image		*img;
	t_fractal	fractal;
	t_vars		vars;

	init_wo_fractal(&vars, &mlx, &win, &img);
	init_fractal(&fractal, N_MAX, args->get_ev, args->param);
	vars.fractal = fractal;
	set_fractal_ev(img, fractal, NULL);
	fractal_to_img(img, fractal);
	mlx_put_image_to_window(mlx, win->win, img->img, 0, 0);
	mlx_key_hook(win->win, &handle_key_input, &vars);
	mlx_mouse_hook(win->win, &handle_mouse_input, &vars);
	mlx_loop(win->mlx);
	free_all(mlx, win, img, 0);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac >= 2)
	{
		fractol_check(ac, av);
		fractol(&mandelbrot);
	}
	else
		print_help();
	return (0);
}
