/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:08:50 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/04 05:54:35 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>

# ifndef WIDTH
#  define WIDTH 800
# endif

# ifndef HEIGHT
#  define HEIGHT 800
# endif

# ifndef X_START
#  define X_START 0
# endif

# ifndef Y_START
#  define Y_START 0
# endif

# ifndef N_MAX
#  define N_MAX 50
# endif

# ifndef ZOOM
#  define ZOOM 1
# endif

typedef struct s_point
{
	double	re;
	double	im;
}	t_point;

typedef struct s_color
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_window {
	void	*mlx;
	void	*win;
	int		hgt;
	int		wid;
}	t_window;

typedef struct s_image {
	void	*mlx;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		wid;
	int		hgt;
	int		*esc_val;
	t_point	min;
	t_point	max;
}	t_image;

typedef struct s_fractal {
	int	N_max;
	int (*get_ev)(t_point, t_point, int, int);
	t_point	param;
}	t_fractal;

typedef struct s_args {
	int (*get_ev)(t_point, t_point, int, int);
	t_point param;
	struct s_args *next;
} t_args;

typedef struct s_vars {
	void *mlx;
	void *win;
	t_image *img;
	t_fractal fractal;
}	t_vars;

// colors.c
int	add_shade(double distance, t_color color);
int	color(int escape_time, int N_max);

// free.c
int	free_window(t_window *win, int exit);
int	free_image(t_image *img, int exit);
int	free_all(void *mlx, t_window *win, t_image *img, int exit);

// init.c
t_window	*init_window(void *mlx, int wid, int hgt);
t_image		*init_image(void *mlx, int wid, int hgt);
int	init_fractal(t_fractal *fractal, int N_max, \
	int (*f)(t_point, t_point, int, int), t_point param);
int	init_wo_fractal(t_vars *vars, void **mlx, t_window **win, t_image **img);

//handle_input.c
int	handle_no_event(void);
int	handle_key_input(int keysym, t_vars *vars);
int	handle_mouse_input(int mousesym, int x, int y, t_vars *vars);

// mandelbrot.c
int		mandelbrot(t_point c, t_point param, int N_max, int n);
int		julia(t_point c, t_point param, int N_max, int n);
int	set_fractal_ev(t_image *img, t_fractal fractal, int *ev_tab);
int	fractal_to_img(t_image *img, t_fractal fractal);

// display.c
int		my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	zoom_mouse(t_image *img, t_point mouse, double t);
int		zoom_point(t_image *img, t_point z, double t);
void	put_grid(t_image *img, int colr);

// points.c
int	set_point(t_point *z, double re, double im);

//translate.c
void	translate_img_1(t_image *img, t_point z, t_fractal frct);
void	translate_img_2(t_image *img, t_point z, t_fractal frct);
void	translate_img_3(t_image *img, t_point z, t_fractal frct);
void	translate_img_4(t_image *img, t_point z, t_fractal frct);
int	translate_img(t_image *img, t_point z, t_fractal frct);

int	ft_putstr_fd(int fd, char *str);
int	fractol(int	(*f)(t_point, int, int));
int	ft_strncmp(const char *s1, const char *s2, size_t n);

t_args *new_arg(int(*get_ev)(t_point, int, int), t_point param);
void	append_args(t_args **x, int(*get_ev)(t_point, int, int), t_point param);
void	free_arg(t_args *arg, int help);
t_point	get_param(char **av, int i, int p, int boucle);
t_args	*fractol_check(int ac, char **av);
void	print_help(void);


#endif
