#include "header.h"

static t_fract	get_mandel()
{
	t_fract	fract;

	fract.number = MANDEL;
	fract.scale = 0.005;
	fract.shift.x = 0;
	fract.shift.y = 0;
	fract.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale";
	fract.file = "./cl/mandel.cl";
	return (fract);
}

static t_fract	get_julia()
{
	t_fract	fract;

	fract.number = JULIA;
	fract.scale = 1;
	fract.shift.x = -0.7;
	fract.shift.y = 0.27015;
	fract.pivot.x = 0.0;
	fract.pivot.y = 0.0;
	fract.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale     J - Julia dancing mode :)";
	fract.file = "./cl/julia.cl";
	return (fract);
}

static t_fract	get_ship()
{
	t_fract	fract;

	fract.number = SHIP;
	fract.scale = 0.005;
	fract.shift.x = 0;
	fract.shift.y = 0;
	fract.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale";
	fract.file = "./cl/ship.cl";
	return (fract);
}

static t_fract	get_tricorn()
{
	t_fract	fract;

	fract.number = TRICORN;
	fract.scale = 0.005;
	fract.shift.x = 0;
	fract.shift.y = 0;
	fract.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale";
	fract.file = "./cl/tricorn.cl";
	return (fract);
}

static t_fract	get_apoll()
{
	t_fract	fract;

	fract.number = APOLL;
	fract.lev = 0;
	fract.man = "UP, DOWN - change number of circles";
	return (fract);
}

static t_fract	get_tree()
{
	t_fract	fract;

	fract.number = TREE;
	fract.lev = 0;
	fract.tilte = 0;
	fract.closeness = 45;
	fract.man = "SCROLL - change number of branches     LEFT, RIGHT - bend branches     UP, DOWN - change branch closeness";
	return (fract);
}

static t_fract	get_cantor()
{
	t_fract	fract;

	fract.number = CANTOR;
	fract.lev = 0;
	fract.len = MIN(WIDTH, HEIGHT) / 2;
	fract.man = "UP, DOWN - change number of cubes     W, A, S, D, Q, E - rotate";
	return (fract);
}

static t_fract	get_serp()
{
	t_fract	fract;

	fract.number = SERP;
	fract.lev = 0;
	fract.len = MIN(WIDTH, HEIGHT) / 1.3;
	fract.man = "UP, DOWN - change number of pyramids     W, A, S, D, Q, E - rotate";
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
	fract.number = -1;
	return (fract);
}
