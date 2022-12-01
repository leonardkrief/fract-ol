/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 05:12:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/01 14:19:05 by lkrief           ###   ########.fr       */
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
		t_point z;
		z.re = -0.95, z.im = 0.25;
		zoom_img(img, z, 100);
		set_mandelbrot_ev(img, 600);
		//mandelbrot_to_img(img, 100);
		mlx_put_image_to_window(mlx, win->mlx_win, img->img, 0, 0);
		mlx_loop(win->mlx);
		return (0);
}
