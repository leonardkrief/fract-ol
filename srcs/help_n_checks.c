/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_n_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:51:15 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/04 04:10:21 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_args *new_arg(int(*get_ev)(t_point, int, int), t_point param)
{
	t_args	*arg;

	arg = malloc(sizeof(*arg));
	if (!arg)
		return (NULL);
	arg->get_ev = get_ev;
	arg->param = param;
	arg->next = NULL;
}

void	append_args(t_args **x, int(*get_ev)(t_point, int, int), t_point param)
{
	t_args	*arg;

	arg = *x;
	if (arg)
	{
		while (arg->next)
			arg = arg->next;
	}
	arg = new_arg(get_ev, param);
}

void	free_arg(t_args *arg, int help)
{
	t_args *tmp;

	while (arg)
	{
		tmp = arg->next;
		free(arg);
		arg = tmp;
	}
	if (help)
		print_help();
}

t_point	get_param(char **av, int i, int p, int boucle)
{
	double	x;
	int		signe;
	double	point;
	t_point	param;

	while (++boucle <= 2)
	{
		x = 0;
		signe = 1;
		while (av[i][p] >= 9 && av[i][p] <= 13 || av[i][p] == ' ')
			p++;
		signe -= 2 * (av[i][p] == '-');
		if (av[i][p] == '+' || av[i][p] == '-')
			p++;
		while (av[i][p] >= '0' && av[i][p] <= '9')
			x = 10 * x + av[i][p++] - '0';
		if (av[i][p] == '.')
			p++;
		point = p;
		while (av[i][p] >= '0' && av[i][p] <= '9')
			x += (av[i][p++] - '0') / pow(10, p - point);
		param.re += signe * x * (boucle == 1);
	}
	param.im = signe * x;
	return (param);
}

t_args	*fractol_check(int ac, char **av)
{
	int		i;
	t_args	*args;

	if (ac < 2)
		print_help();
	tab = malloc(sizeof(*tab) * ac);
	if (!tab)
		return (NULL);
	tab[ac - 1] = NULL;
	i = 0;
	args = NULL;
	while (++i < ac)
	{
		if (ft_strncmp(av[i], "Mandelbrot", 10))
			append_args(&args, mandelbrot, 0);
		else if (ft_strncmp(av[i], "Julia", 4))
			append_args(&args, julia, get_param(av, i, 5, 0));
		else
			free_arg(tab, 1);
	}
	return (tab);
}

void	print_help(void)
{
	ft_putstr_fd("./~|~\\. WELCOME TO MY FRACTALS GENERATOR ./~|~\\.\n\n");
	ft_putstr_fd("Type in ./fract-ol followed by one or several of the");
	ft_putstr_fd("following fractal\n\n");
	ft_putstr_fd("Available fractals: Mandelbrot\n");
	ft_putstr_fd("                    Julia x (where x is a float number)\n\n");
	ft_putstr_fd("Default values:\n");
	ft_putstr_fd("HEIGHT = 800, WIDTH = 800, X_START = 0, Y_START = 0\n");
	ft_putstr_fd("N_MAX = 50, ZOOM = 1\n\n");
	ft_putstr_fd("Examples : ./fract-ol Mandelbrot\n");
	ft_putstr_fd("           ./fract-ol Julia\n");
	ft_putstr_fd("           ./fract-ol Julia 0.454\n\n");
	ft_putstr_fd("While you're running the program, you can press 'h' for help\n");
	ft_putstr_fd("./~\\./~\\. ENJOY AND HAVE FUN ./~\\./~\\.\n");
	exit (0);
}
