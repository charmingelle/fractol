#include "../includes/header.h"

t_circle	get_circle(double center_x, double center_y, double rad)
{
	t_circle	circle;

	circle.center.x = center_x;
	circle.center.y = center_y;
	circle.rad = rad;
	return (circle);
}

t_2point	get_far_center(t_circle c0, t_circle c1, t_circle container,
	double small_rad)
{
	t_2point	first;
	t_2point	second;
	double		d;
	double		a;
	double		h;

	d = sqrt(pow(c0.center.x - c1.center.x, 2)
		+ pow(c0.center.y - c1.center.y, 2));
	a = ((c0.rad + small_rad) * (c0.rad + small_rad)
		- (c1.rad + small_rad) * (c1.rad + small_rad) + d * d) / (2 * d);
	h = sqrt(pow(c0.rad + small_rad, 2) - pow(a, 2));
	first.x = c0.center.x + a * (c1.center.x - c0.center.x)
		/ d + h * (c1.center.y - c0.center.y) / d;
	first.y = c0.center.y + a * (c1.center.y - c0.center.y)
		/ d - h * (c1.center.x - c0.center.x) / d;
	second.x = c0.center.x + a * (c1.center.x - c0.center.x)
		/ d - h * (c1.center.y - c0.center.y) / d;
	second.y = c0.center.y + a * (c1.center.y - c0.center.y)
		/ d + h * (c1.center.x - c0.center.x) / d;
	if (get_2dist(first, container.center) > get_2dist(second, container.center))
		return (first);
	return (second);
}

t_2point	get_close_center(t_circle c0, t_circle c1, t_circle container,
	double small_rad)
{
	t_2point	first;
	t_2point	second;
	double		d;
	double		a;
	double		h;

	d = sqrt(pow(c0.center.x - c1.center.x, 2)
		+ pow(c0.center.y - c1.center.y, 2));
	a = ((c0.rad + small_rad) * (c0.rad + small_rad)
		- (c1.rad + small_rad) * (c1.rad + small_rad) + d * d) / (2 * d);
	h = sqrt(pow(c0.rad + small_rad, 2) - pow(a, 2));
	first.x = c0.center.x + a * (c1.center.x - c0.center.x)
		/ d + h * (c1.center.y - c0.center.y) / d;
	first.y = c0.center.y + a * (c1.center.y - c0.center.y)
		/ d - h * (c1.center.x - c0.center.x) / d;
	second.x = c0.center.x + a * (c1.center.x - c0.center.x)
		/ d - h * (c1.center.y - c0.center.y) / d;
	second.y = c0.center.y + a * (c1.center.y - c0.center.y)
		/ d + h * (c1.center.x - c0.center.x) / d;
	if (get_2dist(first, container.center) < get_2dist(second, container.center))
		return (first);
	return (second);
}

t_2point	get_outer_center(t_env *env, t_2point a, t_2point b, t_2point c)
{
	t_2point	center;
	double		s1;
	double		s2;
	double		s3;

	s1 = get_2dist(a, b);
	s2 = get_2dist(b, c);
	s3 = get_2dist(c, a);
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

t_circle	get_apoll_all(t_circle c0, t_circle c1, t_circle c2)
{
	double		a;
	double		b;
	double		c;
	t_circle	apoll;

	a = 1 / c0.rad;
	b = 1 / c1.rad;
	c = 1 / c2.rad;
	apoll.rad = 1 / (a + b + c + 2 * sqrt(a * b + b * c + c * a));
	apoll.center = get_close_center(c0, c1, c2, apoll.rad);
	return (apoll);
}

void	get_circle_outside_all(t_env *env, int lev, t_circle c[3])
{
	t_circle	new;

	new = get_apoll_all(c[0], c[1], c[2]);
	if (new.rad <= 1)
		return ;
	draw_circle(env, new, lev);
	if (--lev > 1)
	{
		get_circle_outside_all(env, lev, (t_circle[3]){c[0], c[1], new});
		get_circle_outside_all(env, lev, (t_circle[3]){c[0], c[2], new});
		get_circle_outside_all(env, lev, (t_circle[3]){c[1], c[2], new});
	}
}

t_circle	get_apoll_two(t_circle c0, t_circle c1, t_circle c2)
{
	double		a;
	double		b;
	double		c;
	t_circle	apoll;

	a = 1 / c0.rad;
	b = 1 / c1.rad;
	c = -1 / c2.rad;
	apoll.rad = 1 / (a + b + c + 2 * sqrt(a * b + b * c + c * a));
	apoll.center = get_far_center(c0, c1, c2, apoll.rad);
	return (apoll);
}

void	get_circle_outside_two(t_env *env, int lev, t_circle c[3])
{
	t_circle	new;

	new = get_apoll_two(c[0], c[1], c[2]);
	if (new.rad <= 1)
		return ;
	draw_circle(env, new, lev);
	if (--lev > 1)
	{
		get_circle_outside_two(env, lev, (t_circle[3]){new, c[0], c[2]});
		get_circle_outside_two(env, lev, (t_circle[3]){new, c[1], c[2]});
		get_circle_outside_all(env, lev, (t_circle[3]){c[0], c[1], new});
	}
}

void		fill_apoll(t_env *env)
{
	t_circle	c0;
	t_circle	c1;
	t_circle	c2;
	double		rad;
	t_circle	big;

	rad = HEIGHT / 4.315;
	c0 = get_circle(WIDTH / 2, rad, rad);
	c1 = get_circle(WIDTH / 2 - rad, rad + rad * sqrt(3), rad);
	c2 = get_circle(WIDTH / 2 + rad, rad + rad * sqrt(3), rad);
	big = get_outer_circle(env, c0, c1, c2);
	draw_circle(env, big, 0);
	if (env->fract.lev > 0)
	{
		draw_circle(env, c0, 1);
		draw_circle(env, c1, 1);
		draw_circle(env, c2, 1);
	}
	if (env->fract.lev > 1)
	{
		get_circle_outside_all(env, env->fract.lev, (t_circle[3]){c0, c1, c2});
		get_circle_outside_two(env, env->fract.lev, (t_circle[3]){c0, c1, big});
		get_circle_outside_two(env, env->fract.lev, (t_circle[3]){c1, c2, big});
		get_circle_outside_two(env, env->fract.lev, (t_circle[3]){c2, c0, big});
	}
}
