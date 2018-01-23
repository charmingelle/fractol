#include "header.h"

static t_point	get_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

static t_point	get_moved_point(t_point point, double x_shift, double y_shift, double z_shift)
{
	t_point	moved;

	moved.x = point.x + x_shift;
	moved.y = point.y + y_shift;
	moved.z = point.z + z_shift;
	return (moved);
}

static t_square	get_square(t_point start, int len)
{
	t_square	square;

	square.a = get_moved_point(start, 0, 0, 0);
	square.b = get_moved_point(start, len - 1, 0, 0);
	square.c = get_moved_point(start, len - 1, len - 1, 0);
	square.d = get_moved_point(start, 0, len - 1, 0);
	return (square);
}

static void		draw_seg(t_env *env, t_point p1, t_point p2)
{
	double	step;
	double	t;
	t_point	mid;
	int		pos;

	step = 0.5 / sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	t = 0;
	while (t <= 1)
	{
		mid.x = (p2.x - p1.x) * t + p1.x;
		mid.y = (p2.y - p1.y) * t + p1.y;
		mid.z = (p2.z - p1.z) * t + p1.z;
		pos = (int)mid.y * WIDTH + (int)mid.x;
		if ((mid.x > 0 && mid.x < WIDTH && mid.y > 0 && mid.y < HEIGHT) && (env->z_buff[pos] == 0 || env->z_buff[pos] < mid.z))
		{
			env->z_buff[pos] = mid.z;
			env->image_data[pos] = GREEN;
		}
		t += step;
	}
}

static void		draw_square(t_env *env, t_square square, int len, int step)
{
	t_square	new1;
	t_square	new2;
	t_square	new3;
	t_square	new4;
	

	draw_seg(env, square.a, square.b);
	draw_seg(env, square.b, square.c);
	draw_seg(env, square.c, square.d);
	draw_seg(env, square.d, square.a);
	len /= 3;
	if (step < env->fract.lev && len > 1)
	{
		new1 = get_square(square.a, len);
		draw_square(env, new1, len, step + 1);
		new2 = get_square(get_moved_point(square.b, -len + 1, 0, 0), len);
		draw_square(env, new2, len, step + 1);
		new3 = get_square(get_moved_point(square.c, -len + 1, -len + 1, 0), len);
		draw_square(env, new3, len, step + 1);
		new4 = get_square(get_moved_point(square.d, 0, -len + 1, 0), len);
		draw_square(env, new4, len, step + 1);
	}
}

void			fill_cantor(t_env *env)
{
	int			len;
	t_square	square;

	len = MIN(WIDTH, HEIGHT);
	square = get_square(get_point((WIDTH / 2) - (len / 2), 0, 0), len);
	draw_square(env, square, len, 0);
}
