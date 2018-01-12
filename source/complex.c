#include "header.h"

double		get_re(t_complex a)
{
	return (a.re);
}

double		get_im(t_complex a)
{
	return (a.im);
}

t_complex	get_sum(t_complex a, t_complex b)
{
	t_complex	sum;

	sum.re = a.re + b.re;
	sum.im = a.im + b.im;
	return (sum);
}

t_complex	get_prod(t_complex a, t_complex b)
{
	t_complex	prod;

	prod.re = a.re * b.re - a.im * b.im;
	prod.im = a.im * b.re + a.re * b.im;
	return (prod);
}

double	  get_mod(t_complex a)
{
	return (sqrt(pow(a.re, 2) + pow(a.im, 2)));
}
