#include "header.h"

double		get_dist(t_2point a, t_2point b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

t_circle	get_circle(t_2point center, double rad)
{
	t_circle	circle;

	circle.center = center;
	circle.rad = rad;
	return (circle);
}

t_2point	get_2point(double x, double y)
{
	t_2point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_2point	get_center(t_circle c0, t_circle c1, t_circle container, double small_rad, int side)
{
	t_2point	first;
	t_2point	second;
	double		d;
	double		a;
	double		h;

	d = sqrt(pow(c0.center.x - c1.center.x, 2) + pow(c0.center.y - c1.center.y, 2));
	a = ((c0.rad + small_rad) * (c0.rad + small_rad) - (c1.rad + small_rad) * (c1.rad + small_rad) + d * d ) / (2 * d);
	h = sqrt(pow(c0.rad + small_rad, 2) - pow(a, 2));
	first.x = c0.center.x + a * (c1.center.x - c0.center.x) / d + h * (c1.center.y - c0.center.y) / d;
	first.y = c0.center.y + a * (c1.center.y - c0.center.y) / d - h * (c1.center.x - c0.center.x) / d;
	second.x = c0.center.x + a * (c1.center.x - c0.center.x) / d - h * (c1.center.y - c0.center.y) / d;
	second.y = c0.center.y + a * (c1.center.y - c0.center.y) / d + h * (c1.center.x - c0.center.x) / d;
	if (side * get_dist(first, container.center) > side * get_dist(second, container.center))
		return (first);
	return (second);
}

t_2point	get_outer_center(t_env *env, t_2point a, t_2point b, t_2point c)
{
	t_2point	center;
	double		s1;
	double		s2;
	double		s3;

	s1 = get_dist(a, b);
	s2 = get_dist(b, c);
	s3 = get_dist(c, a);
	center.x = (s1 * a.x + s2 * b.x + s3 * c.x) / (s1 + s2 + s3);
	center.y = (s1 * a.y + s2 * b.y + s3 * c.y) / (s1 + s2 + s3);
	return (center);
}

t_circle	get_outer_circle(t_env *env, t_circle c0, t_circle c1, t_circle c2)
{
	double		a;
	double		b;
	double		c;
	t_circle	apoll;

	a = -1 / c0.rad;
	b = -1 / c1.rad;
	c = -1 / c2.rad;
	apoll.rad = 1 / (a + b + c + 2 * sqrt(a * b + b * c + c * a));
	apoll.center = get_outer_center(env, c0.center, c1.center, c2.center);
	return (apoll);
}

t_circle	get_apoll_circle(t_env *env, t_circle c0, t_circle c1, t_circle c2, int k0, int k1, int k2)
{
	double		a;
	double		b;
	double		c;
	t_circle	apoll;

	a = k0 / c0.rad;
	b = k1 / c1.rad;
	c = k2 / c2.rad;
	apoll.rad = 1 / (a + b + c + 2 * sqrt(a * b + b * c + c * a));
	if (k0 == k1 && k1 == k2)
		apoll.center = get_center(c0, c1, c2, apoll.rad, -1);
	else
		apoll.center = get_center(c0, c1, c2, apoll.rad, 1);
	return (apoll);
}

void	get_circle_outside_all(t_env *env, int level, t_circle c0, t_circle c1, t_circle c2)
{
	t_circle	new;

	new = get_apoll_circle(env, c0, c1, c2, 1, 1, 1);
	if (new.rad <= 1)
		return ;
	draw_circle(env, new);
	if (--level > 1)
	{
		get_circle_outside_all(env, level, c0, c1, new);
		get_circle_outside_all(env, level, c0, c2, new);
		get_circle_outside_all(env, level, c1, c2, new);
	}
}

void	get_circle_outside_two(t_env *env, int level, t_circle c0, t_circle c1, t_circle container)
{
	t_circle	new;

	new = get_apoll_circle(env, c0, c1, container, 1, 1, -1);
	if (new.rad <= 1)
		return ;
	draw_circle(env, new);
	if (--level > 1)
	{
		get_circle_outside_two(env, level, new, c0, container);
		get_circle_outside_two(env, level, new, c1, container);
		get_circle_outside_all(env, level, c0, c1, new);
	}
}

void		fill_apoll(t_env *env)
{
	t_circle	c0;
	t_circle	c1;
	t_circle	c2;
	t_2point	center;
	double		rad;
	t_circle	big_circle;

	rad = HEIGHT / 4.315;
	center = get_2point(WIDTH / 2, rad);
	c0 = get_circle(center, rad);
	center = get_2point(center.x - rad, center.y + rad * sqrt(3));
	c1 = get_circle(center, rad);
	center = get_2point(center.x + 2* rad, center.y);
	c2 = get_circle(center, rad);
	big_circle = get_outer_circle(env, c0, c1, c2);
	draw_circle(env, big_circle);
	if (env->fract.level > 0)
	{
		draw_circle(env, c0);
		draw_circle(env, c1);
		draw_circle(env, c2);
	}
	if (env->fract.level > 1)
	{
		get_circle_outside_all(env, env->fract.level, c0, c1, c2);
		get_circle_outside_two(env, env->fract.level, c0, c1, big_circle);
		get_circle_outside_two(env, env->fract.level, c1, c2, big_circle);
		get_circle_outside_two(env, env->fract.level, c2, c0, big_circle);
	}
}
