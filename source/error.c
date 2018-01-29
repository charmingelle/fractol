#include "../includes/header.h"

int show_usage_error()
{
	ft_putstr("usage: ./fract number\n");
	ft_putstr("1 - Mandelbrot\n, 2 - Julia\n, 3 - Burning Ship\n, 4 - Tricorn\n, 5 - Apollonian Gasket\n, 6 - Pythagoras Tree\n, 7 - Cantor Dust 3D\n, 8 - Sierpinski Pyramid\n");
	return (1);
}
