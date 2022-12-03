/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 05:12:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/03 00:19:07 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	main(void)
{
	t_window	*win;
	t_image		*img;
	int			wid;
	int			hgt;
	void	*mlx;

		wid = 800;
		hgt = 800;
		mlx = mlx_init();
		if (mlx == NULL)
			return (-1);
		win = init_window(mlx, wid, hgt);
		if (!win)
			return (-1);
		img = init_image(mlx, wid, hgt);
		if (!img)
			return(-1); // il faudra free le window
		t_fractal fractal;
		fractal.N_max = 100;
		fractal.get_ev = *mandelbrot;
		t_point z, a;
		z.re = 0.5, z.im = -0.5;
		a.re = 1, a.im = 1;
		zoom_point(img, z, 1);
		set_fractal_ev(img, fractal, NULL, 0);
		fractal_to_img(img, fractal);
		//put_grid(img, 0x000000ff);
		mlx_put_image_to_window(mlx, win->mlx_win, img->img, 0, 0);

		translate_img(img, a, fractal);
		fractal_to_img(img, fractal);
		put_grid(img, 0x000ff000);
		mlx_put_image_to_window(mlx, win->mlx_win, img->img, 0, 0);

		mlx_loop(win->mlx);
		return (0);
}
