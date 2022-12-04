/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 22:32:59 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/03 23:17:58 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	free_window(t_window *win, int exit_code)
{
	if (!win || !win->mlx)
		return (-1);
	if (win->win)
		mlx_destroy_window(win->mlx, win->win);
	win->win = NULL;
	free(win);
	if (exit_code)
		exit (exit_code);
	return (0);
}

int	free_image(t_image *img, int exit_code)
{
	if (!img || !img->mlx)
		return (-1);
	if (img->img)
		mlx_destroy_image(img->mlx, img->img);
	img->img = NULL;
	if (img->esc_val)
		free(img->esc_val);
	img->esc_val = NULL;
	free(img);
	if (exit_code)
		exit (exit_code);
	return (0);
}

int	free_all(void *mlx, t_window *win, t_image *img, int exit_code)
{
	int i;

	i = 0;
	if (img)
		i += free_image(img, exit_code);
	if (win)
		i += free_window(win, exit_code);
	if (mlx)
		// mlx_destroy_ptr(mlx);
	if (exit_code)
		exit (exit_code);
	return (i);
}
