/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 05:12:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/02 02:43:01 by lkrief           ###   ########.fr       */
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

		wid = 500;
		hgt = 500;
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
		fractal.N_max = 250;
		fractal.get_ev = *mandelbrot;
		t_point z, a;
		z.re = 1, z.im = -1;
		a.re = 0, a.im = 0;
		// zoom_img(img, z, 250);
		set_fractal_ev(img, fractal, NULL, 0);
		fractal_to_img(img, fractal);
		put_grid(img, 0x000000ff);
		mlx_put_image_to_window(mlx, win->mlx_win, img->img, 0, 0);

		translate_img(img, z, fractal);
		fractal_to_img(img, fractal);
		put_grid(img, 0xa0000000);
		mlx_put_image_to_window(mlx, win->mlx_win, img->img, 0, 0);

		mlx_loop(win->mlx);
		return (0);
}
