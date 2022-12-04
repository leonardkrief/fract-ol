/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_n_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:51:15 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/04 15:56:01 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_args *new_arg(int(*get_ev)(t_point, t_point, int, int), t_point param)
{
	t_args	*arg;

	arg = malloc(sizeof(*arg));
	if (!arg)
		return (NULL);
	arg->get_ev = get_ev;
	arg->param = param;
	arg->next = NULL;
	return (arg);
}

void	append_args(t_args **arg, int(*get_ev)(t_point, t_point, int, int), t_point param)
{
	if (!(*arg))
		*arg = new_arg(get_ev, param);
	else
	{
		while ((*arg)->next)
			(*arg) = (*arg)->next;
		(*arg)->next = new_arg(get_ev, param);
	}
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
		while ((av[i][p] >= 9 && av[i][p] <= 13) || av[i][p] == ' ')
			p++;
		signe -= 2 * (av[i][p] == '-');
		if (av[i][p] == '+' || av[i][p] == '-')
			p++;
		while (av[i][p] >= '0' && av[i][p] <= '9')
			x = 10 * x + av[i][p++] - '0';
		if (av[i][p] == '.')
			p++;
		point = p - 1;
		while (av[i][p] >= '0' && av[i][p] <= '9')
		{
			x += (av[i][p] - '0') / pow(10, p - point);
			p++;
		}
		param.re += signe * x * (boucle == 1);
	}
	param.im = signe * x;
	return (param);
}

t_args	*fractol_check(int ac, char **av)
{
	int		i;
	t_args	*args;
	t_point	param;

	if (ac < 2)
		print_help();
	set_point(&param, 0, 0);
	args = NULL;
	i = 0;
	while (++i < ac)
	{
		if (!ft_strncmp(av[i], "Mandelbrot", 10))
			append_args(&args, mandelbrot, param);
		else if (!ft_strncmp(av[i], "Julia", 5))
			append_args(&args, julia, get_param(av, i, 5, 0));
		else
			free_arg(args, 1);
	}
	return (args);
}



void	print_help(void)
{
	ft_putstr("\n");
	ft_putstr(" ~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~\n");
	ft_putstr(" ~.~.~.~.~.~.WELCOME TO MY FRACTALS GENERATOR.~.~..~.~.~.~.~\n");
	ft_putstr(" ~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~");
	ft_putstr("\n\n ./fract-ol followed by one or several of the ");
	ft_putstr("following fractal\n\n");
	ft_putstr(" Available fractals: \"Mandelbrot\"\n");
	ft_putstr("                     \"Julia x\" (x is a float number)\n\n");
	// ft_putstr("Default values:\n");
	// ft_putstr("HEIGHT = 800, WIDTH = 800, X_START = 0, Y_START = 0\n");
	// ft_putstr("N_MAX = 50, ZOOM = 1\n\n");
	ft_putstr(" Examples : ./fract-ol Mandelbrot\n");
	ft_putstr("            ./fract-ol Julia\n");
	ft_putstr("            ./fract-ol \"Julia 0.454+0.12i\"\n\n");
	ft_putstr(" While you run the program, you can press 'h' for help\n\n");
	ft_putstr(" ~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~\n");
	ft_putstr(" ~.~.~.~.~.~.~.~.~.~.~.~.ENJOY!.~.~.~..~.~.~..~.~..~.~.~.~.~\n");
	ft_putstr(" ~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~");
	ft_putstr("\n");
	exit (0);
}
