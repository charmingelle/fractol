#include "../includes/header.h"

t_fract	get_mandel()
{
	t_fract	fract;

	fract.number = MANDEL;
	fract.scale = 0.005;
	fract.shift.re = -0.75;
	fract.shift.im = 0;
	return (fract);
}

t_fract	get_julia()
{
	t_fract	fract;

	fract.number = JULIA;
	fract.scale = 1;
	fract.shift.re = -0.7;
	fract.shift.im = 0.27015;
	fract.pivot.re = 0.0;
	fract.pivot.re = 0.1;
	return (fract);
}

t_fract	get_ship()
{
	t_fract	fract;

	fract.number = SHIP;
	fract.scale = 0.005;
	fract.shift.re = -0.75;
	fract.shift.im = 0;
	return (fract);
}

t_fract	get_tricorn()
{
	t_fract	fract;

	fract.number = TRICORN;
	fract.scale = 0.005;
	fract.shift.re = -0.75;
	fract.shift.im = 0;
	return (fract);
}

t_fract	get_apoll()
{
	t_fract	fract;

	fract.number = APOLL;
	fract.lev = 0;
	return (fract);
}

t_fract	get_tree()
{
	t_fract	fract;

	fract.number = TREE;
	fract.lev = 0;
	fract.tilte = 0;
	fract.closeness = 45;
	return (fract);
}

t_fract	get_cantor()
{
	t_fract	fract;

	fract.number = CANTOR;
	fract.lev = 0;
	fract.len = MIN(WIDTH, HEIGHT) / 2;
	return (fract);
}

t_fract	get_serp()
{
	t_fract	fract;

	fract.number = SERP;
	fract.lev = 0;
	fract.len = MIN(WIDTH, HEIGHT) / 1.3;
	return (fract);
}

t_fract	get_fract_data(int number)
{
	t_fract	fract;

	if (number == MANDEL)
		return (get_mandel());
	if (number == JULIA)
		return (get_julia());
	if (number == SHIP)
		return (get_ship());
	if (number == TRICORN)
		return (get_tricorn());
	if (number == APOLL)
		return (get_apoll());
	if (number == TREE)
		return (get_tree());
	if (number == CANTOR)
		return (get_cantor());
	if (number == SERP)
		return (get_serp());
	return (fract);
}
