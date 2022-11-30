/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 05:12:05 by lkrief            #+#    #+#             */
/*   Updated: 2022/11/30 16:12:33 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

int	main(void)
{
	t_window	*win;
	t_image		*img;
	int			wid;
	int			len;

	wid = 800;
	len = 800;
	win = init_window(wid, len);
	if (!win)
		return (-1);
	img = init_image(win, wid, len);
	if (!img)
		return(-1); // il faudra free le window
	mandelbrot_to_win(win, img);
	return (0);
}
