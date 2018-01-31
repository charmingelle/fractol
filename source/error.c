#include "header.h"

int show_usage_error()
{
	ft_putstr_fd("usage: ./fractol number\n1 - Mandelbrot\n2 - Julia\n3 - Burning Ship\n4 - Tricorn\n5 - Apollonian Gasket\n6 - Pythagoras Tree\n7 - Cantor Dust 3D\n8 - Sierpinski Pyramid\n", 2);
	return (1);
}

int	show_kernel_error()
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
