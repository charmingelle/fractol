#include "../includes/header.h"

int show_usage_error()
{
	ft_putstr("usage: ./fract 1 [2] [3]\n");
	ft_putstr("1 - Mandelbrot, 2 - Julia, 3 - Some other fract\n");
	return (1);
}
