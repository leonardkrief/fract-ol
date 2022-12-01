/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 05:12:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/01 14:52:06 by lkrief           ###   ########.fr       */
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
	int		N_max;

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
		t_point z;
		z.re = -0.95, z.im = 0.25;
		zoom_img(img, z, 250);
		N_max = 1000;
		set_mandelbrot_ev(img, N_max, NULL, 0);
		mandelbrot_to_img(img, N_max);
		mlx_put_image_to_window(mlx, win->mlx_win, img->img, 0, 0);
		int x = -1, y = -1;
		while (++x < img->wid)
		{
			y = img->hgt;
			while (--y > -1)
				printf("%x ", img->esc_val[y * img->wid + x]);
			printf("\n");
		}
		mlx_loop(win->mlx);
		return (0);
}
