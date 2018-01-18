#include "header.h"

t_circle	get_circle(t_2point center, double rad)
{
	t_circle	circle;

	circle.center = center;
	circle.rad = rad;
	return (circle);
}

t_2point	get_kissing_point(t_circle a, t_circle b)
{
	t_2point	kiss;

	kiss.x = a.center.x + a.rad * (b.center.x - a.center.x) / (a.rad + b.rad);
	kiss.y = a.center.y + a.rad * (b.center.y - a.center.y) / (a.rad + b.rad);
	printf("(%f, %f) - (%f, %f)\n", a.center.x, a.center.y, b.center.x, b.center.y);
	printf("(%f, %f)\n", kiss.x, kiss.y);
	return (kiss);
}

double		get_dist(t_2point a, t_2point b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

t_2point	get_outside_two_center(t_circle a, t_circle b, t_circle outer, double small_rad)
{
	t_2point	kiss;
	t_2point	center;
	double		dist;

	kiss = get_kissing_point(a, b);
	dist = get_dist(kiss, outer.center);
	center.x = (outer.rad - small_rad) * (kiss.x - outer.center.x) / dist + outer.center.x;
	center.y = (outer.rad - small_rad) * (kiss.y - outer.center.y) / dist + outer.center.y;
	return (center);
}

t_2point	get_outside_all_center(t_2point a, t_2point b, t_2point c)
{
	t_2point	center;
	double		d;

	d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
	center.x = ((pow(a.x, 2) + pow(a.y, 2)) * (b.y - c.y)
	+ (pow(b.x, 2) + pow(b.y, 2)) * (c.y - a.y)
	+ (pow(c.x, 2) + pow(c.y, 2)) * (a.y - b.y)) / d;
	center.y = ((pow(a.x, 2) + pow(a.y, 2)) * (c.x - b.x)
	+ (pow(b.x, 2) + pow(b.y, 2)) * (a.x - c.x)
	+ (pow(c.x, 2) + pow(c.y, 2)) * (b.x - a.x)) / d;
	return (center);
}

t_circle	*get_apoll_circle(t_circle c0, t_circle c1, t_circle c2, int k0, int k1, int k2)
{
	double		a;
	double		b;
	double		c;
	t_circle	*apoll;

	a = k0 / c0.rad;
	b = k1 / c1.rad;
	c = k2 / c2.rad;
	apoll = (t_circle *)malloc(sizeof(t_circle));
	// apoll->x = WIDTH / 2;
	// apoll->y = c0.y + (2 * c0.rad) / sqrt(3);
	apoll->rad = 1 / (a + b + c + 2 * sqrt(a * b + b * c + c * a));
	if (k0 == k1 && k1 == k2)
		apoll->center = get_outside_all_center(c0.center, c1.center, c2.center);
	else
		apoll->center = get_outside_two_center(c0, c1, c2, apoll->rad);
	return (apoll);
}

void	get_circle_outside_two(t_env *env, int level, t_circle c0, t_circle c1, t_circle container)
{
	t_circle	*new;

	new = get_apoll_circle(c0, c1, container, 1, 1, -1);
	if (new == NULL || new->rad < 0.1)
		return ;
	draw_circle(env, *new);
	if (--level > 0)
	{
		get_circle_outside_two(env, level, *new, c0, container);
		get_circle_outside_two(env, level, *new, c1, container);
	// 	get_circle_outside_two(env, level, c0, c1, *new);
	}
}

void	get_circle_outside_all(t_env *env, int level, t_circle c0, t_circle c1, t_circle c2)
{
	t_circle	*new;

	new = get_apoll_circle(c0, c1, c2, 1, 1, 1);
	if (new == NULL || new->rad < 0.1)
		return ;
	draw_circle(env, *new);
	if (--level > 0)
	{
		get_circle_outside_all(env, level, c0, c1, *new);
		get_circle_outside_all(env, level, c0, c2, *new);
		get_circle_outside_all(env, level, c1, c2, *new);
	}
}

void		fill_apoll(t_env *env)
{
	t_circle	c0;
	t_circle	c1;
	t_circle	c2;
	t_2point	center;
	double		rad;
	// double	gasket_height;
	t_circle	*big_circle;
	int			level;

	rad = HEIGHT / (2 + 2 * sqrt(3) / 2);
	center.x = WIDTH / 2;
	// gasket_height = 2 * (rad + 2 * rad / sqrt(3));
	center.y = rad;
	c0 = get_circle(center, rad);

	center.x -= rad;
	center.y += rad * sqrt(3);
	c1 = get_circle(center, rad);
	center.x += 2 * rad;
	c2 = get_circle(center, rad);

	draw_circle(env, c0);
	draw_circle(env, c1);
	draw_circle(env, c2);
	big_circle = get_apoll_circle(c0, c1, c2, -1, -1, -1);
	draw_circle(env, *big_circle);
	level = 10;
	get_circle_outside_all(env, level, c0, c1, c2);
	get_circle_outside_two(env, level, c0, c1, *big_circle);
	get_circle_outside_two(env, level, c1, c2, *big_circle);
	get_circle_outside_two(env, level, c2, c0, *big_circle);
}
