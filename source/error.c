/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:17 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 19:56:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	show_usage_error(void)
{
	ft_putstr_fd("usage: ./ftol number\n1 - Mandelbrot\n2 - Julia\n", 2);
	ft_putstr_fd("3 - Burning Ship\n4 - Tricorn\n5 - Apollonian Gasket\n", 2);
	ft_putstr_fd("6 - Pythagoras Tree\n7 - Cantor Dust 3D\n", 2);
	ft_putstr_fd("8 - Sierpinski Pyramid\n", 2);
	return (1);
}

int	show_kernel_error(void)
{
	ft_putstr_fd("Failed to load kernel\n", 2);
	return (1);
}

int	show_set_param_error(char *param)
{
	ft_putstr_fd("Can't set kernel parameter ", 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
