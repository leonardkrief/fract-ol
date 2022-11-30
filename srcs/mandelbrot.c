#include "../include/fract-ol.h"

int	mandelbrot_radius(t_point *c, int precision)
{
	t_point	*z;
	t_point	*tmp;

	z = init_point(0, 0);
	if (!z)
		exit_points(c, NULL);
	while (module_point(z) <= 2 && --precision > 0)
	{
		tmp = init_point(z->re, z->im);
		if (!tmp)
			exit_points(z, c);
		z->re = pow(tmp->re, 2) - pow(tmp->im, 2) + c->re;
		z->im = 2 * tmp->re * tmp->im + c->im;
		free(tmp);
	}
	free(z);
	return (precision);
}

void	mandelbrot_to_win(t_window *win, t_image *img)
{
	int		i;
	int		j;
	int		color;
	t_point	*c;

	i = -1;
	while (++i < win->wid)
	{
		j = -1;
		while (++j < win->len)
		{
			c = init_point(-2 + ((double)i) * 4 / win->wid, -2 + ((double)j) * 4 / win->len);
			if (!c)
				exit_points(NULL, NULL);
			color = mandelbrot_radius(c, 100);
			if (!color)
				my_mlx_pixel_put(img, i, j, module_point(c) * 10000);
			else if (color < 88)
				my_mlx_pixel_put(img, i, j, pow(color, 2) * 100000);
			else
				my_mlx_pixel_put(img, i, j, 10000000);
			free(c);
		}
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, img->img, 0, 0);
	mlx_loop(win->mlx);
}
