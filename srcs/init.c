#include "../include/fract-ol.h"

t_window *init_window(int wid, int len)
{
	t_window	*win;

	win = malloc(sizeof(*win));
	if (!win)
		return(NULL);
	win->mlx = mlx_init(); // proteger ?
	win->mlx_win = mlx_new_window(win->mlx, wid, len, "fract-ol"); // proteger ?
	win->wid = wid;
	win->len = len;
	return (win);
}

t_image *init_image(t_window *win, int wid, int len)
{
	t_image	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return(NULL);
	img->img = mlx_new_image(win->mlx, wid, len); // proteger ?
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), \
					&(img->line_length), &(img->endian)); // proteger ?
	return (img);
}
