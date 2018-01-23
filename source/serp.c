#include "header.h"

static t_2point	get_2point(double x, double y)
{
	t_2point	point;

	point.x = x;
	point.y = y;
	return (point);
}

static t_2point	get_middle(t_2point a, t_2point b)
{
	t_2point	middle;

	middle.x = (a.x + b.x) / 2;
	middle.y = (a.y + b.y) / 2;
	return (middle);
}

static t_triag		get_triag(t_2point a, t_2point b, t_2point c)
{
	t_triag	triag;

	triag.a = a;
	triag.b = b;
	triag.c = c;
	return (triag);
}

static void		draw_seg(t_env *env, t_2point p1, t_2point p2)
{
	double	step;
	double	t;
	int		x;
	int		y;

	step = 0.5 / sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	t = 0;
	while (t < 1)
	{
		x = (p2.x - p1.x) * t + p1.x;
		y = (p2.y - p1.y) * t + p1.y;
		env->image_data[y * WIDTH + x] = WHITE;
		t += step;
	}
}

static void		draw_triag(t_env *env, t_triag triag)
{
	draw_seg(env, triag.a, triag.b);
	draw_seg(env, triag.a, triag.c);
	draw_seg(env, triag.b, triag.c);
}

static void		recur(t_env *env, t_triag triag, int step)
{
	t_2point	m1;
	t_2point	m2;
	t_2point	m3;

	draw_triag(env, triag);
	m1 = get_middle(triag.a, triag.b);
	m2 = get_middle(triag.b, triag.c);
	m3 = get_middle(triag.a, triag.c);
	if (step < env->fract.lev && get_dist(m1, m2) > 1.0)
	{
		recur(env, get_triag(triag.a, m1, m3), step + 1);
		recur(env, get_triag(triag.b, m1, m2), step + 1);
		recur(env, get_triag(triag.c, m2, m3), step + 1);
	}
}

void		fill_serp(t_env *env)
{
	int	step;

	step = 0;
	recur(env,
		get_triag(get_2point(WIDTH / 2, 0),
		get_2point(WIDTH / 2 - HEIGHT / sqrt(3), HEIGHT - 1),
		get_2point(WIDTH / 2 + HEIGHT / sqrt(3), HEIGHT - 1)), step);
}
