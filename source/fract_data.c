#include "header.h"

static t_ft	get_mandel(void)
{
	t_ft	ft;

	ft.number = MANDEL;
	ft.scale = 0.005;
	ft.shift.x = 0;
	ft.shift.y = 0;
	ft.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale";
	ft.file = "./cl/mandel.cl";
	return (ft);
}

static t_ft	get_julia(void)
{
	t_ft	ft;

	ft.number = JULIA;
	ft.scale = 1;
	ft.shift.x = -0.7;
	ft.shift.y = 0.27015;
	ft.pivot.x = 0.0;
	ft.pivot.y = 0.0;
	ft.man = "LEFT, RIGHT, UP, DOWN - move     \
		SCROLL - change scale     \
		J - Julia dancing mode :)";
	ft.file = "./cl/julia.cl";
	return (ft);
}

static t_ft	get_ship(void)
{
	t_ft	ft;

	ft.number = SHIP;
	ft.scale = 0.005;
	ft.shift.x = 0;
	ft.shift.y = 0;
	ft.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale";
	ft.file = "./cl/ship.cl";
	return (ft);
}

static t_ft	get_tricorn(void)
{
	t_ft	ft;

	ft.number = TRICORN;
	ft.scale = 0.005;
	ft.shift.x = 0;
	ft.shift.y = 0;
	ft.pivot.x = 0.0;
	ft.pivot.y = 0.0;
	ft.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale";
	ft.file = "./cl/tricorn.cl";
	return (ft);
}

static t_ft	get_apoll(void)
{
	t_ft	ft;

	ft.number = APOLL;
	ft.scale = 1.0;
	ft.shift.x = 0.0;
	ft.shift.y = 0.0;
	ft.lev = 0;
	ft.man = "PLUS, MINUS - change number of circles     \
		LEFT, RIGHT, UP, DOWN - move";
	return (ft);
}

static t_ft	get_tree(void)
{
	t_ft	ft;

	ft.number = TREE;
	ft.lev = 0;
	ft.tilte = 0;
	ft.close = 45;
	ft.man = "SCROLL - change number of branches     \
		LEFT, RIGHT - bend branches     \
		UP, DOWN - change branch close";
	return (ft);
}

static t_ft	get_cantor(void)
{
	t_ft	ft;

	ft.number = CANTOR;
	ft.lev = 0;
	ft.len = MIN(WIDTH, HEIGHT) / 2;
	ft.man = "UP, DOWN - change number of cubes     W, A, S, D, Q, E - rotate";
	return (ft);
}

static t_ft	get_serp(void)
{
	t_ft	ft;

	ft.number = SERP;
	ft.lev = 0;
	ft.len = MIN(WIDTH, HEIGHT) / 1.3;
	ft.man = "UP, DOWN - change number of pyramids     \
		W, A, S, D, Q, E - rotate";
	return (ft);
}

t_ft	get_ft_data(int number)
{
	t_ft	ft;

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
	ft.number = -1;
	return (ft);
}
