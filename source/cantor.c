#include "header.h"

inline static t_point	get_moved_point(t_point point, double x_shift,
										double y_shift, double z_shift)
{
	return ((t_point){point.x + x_shift, point.y + y_shift, point.z + z_shift});
}

static t_cube			get_cube(t_point start, int len)
{
	t_cube	cube;

	cube.front_a = start;
	cube.front_b = get_moved_point(start, len - 1, 0, 0);
	cube.front_c = get_moved_point(start, len - 1, len - 1, 0);
	cube.front_d = get_moved_point(start, 0, len - 1, 0);
	cube.back_a = get_moved_point(start, 0, 0, len - 1);
	cube.back_b = get_moved_point(start, len - 1, 0, len - 1);
	cube.back_c = get_moved_point(start, len - 1, len - 1, len - 1);
	cube.back_d = get_moved_point(start, 0, len - 1, len - 1);
	return (cube);
}

void				draw_seg(t_env *env, t_point a, t_point b,
								int color)
{
	double	step;
	double	t;
	t_point	mid;
	int		pos;

	a = get_modified_point(env, a);
	b = get_modified_point(env, b);
	step = 0.5 / sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	t = 0;
	while (t <= 1)
	{
		mid.x = (b.x - a.x) * t + a.x;
		mid.y = (b.y - a.y) * t + a.y;
		mid.z = (b.z - a.z) * t + a.z;
		pos = (int)mid.y * WIDTH + (int)mid.x;
		if ((mid.x > 0 && mid.x < WIDTH && mid.y > 0 && mid.y < HEIGHT)
			&& (env->z_buff[pos] == 0 || env->z_buff[pos] < mid.z))
		{
			env->z_buff[pos] = mid.z;
			env->image_data[pos] = color;
		}
		t += step;
	}
}

static void				draw_parallelogram(t_env *env, t_point a[2],
											t_point b[2], int color)
{
	double	t;
	double	step;
	t_point	temp1;
	t_point	temp2;

	step = 0.5 / sqrt((a[0].x - a[1].x) * (a[0].x - a[1].x)
		+ (a[0].y - a[1].y) * (a[0].y - a[1].y));
	t = -step;
	while ((t += step) <= 1)
	{
		temp1.x = (a[1].x - a[0].x) * t + a[0].x;
		temp1.y = (a[1].y - a[0].y) * t + a[0].y;
		temp1.z = (a[1].z - a[0].z) * t + a[0].z;
		temp2.x = (b[1].x - b[0].x) * t + b[0].x;
		temp2.y = (b[1].y - b[0].y) * t + b[0].y;
		temp2.z = (b[1].z - b[0].z) * t + b[0].z;
		draw_seg(env, temp1, temp2, color);
	}
}

static void				draw_cube(t_env *env, t_cube cube)
{
	draw_parallelogram(env, (t_point[2]){cube.front_a, cube.front_b},
							(t_point[2]){cube.front_d, cube.front_c}, 0xF5BC0C);
	draw_parallelogram(env, (t_point[2]){cube.back_a, cube.back_b},
							(t_point[2]){cube.back_d, cube.back_c}, 0xF59018);
	draw_parallelogram(env, (t_point[2]){cube.front_a, cube.front_b},
							(t_point[2]){cube.back_a, cube.back_b}, 0x751E16);
	draw_parallelogram(env, (t_point[2]){cube.front_b, cube.front_c},
							(t_point[2]){cube.back_b, cube.back_c}, 0xBD2404);
	draw_parallelogram(env, (t_point[2]){cube.front_c, cube.front_d},
							(t_point[2]){cube.back_c, cube.back_d}, 0x750401);
	draw_parallelogram(env, (t_point[2]){cube.front_d, cube.front_a},
							(t_point[2]){cube.back_d, cube.back_a}, 0xF26105);
}

static void				cantor_recur(t_env *env, t_cube cube, int len, int step)
{
	len /= 3;
	if (step < env->fract.lev && len > 1)
	{
		cantor_recur(env, get_cube(cube.front_a, len),
									len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.front_b, -len + 1,
									0, 0), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.front_c, -len + 1,
									-len + 1, 0), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.front_d, 0, -len + 1,
									0), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.back_a, 0, 0,
									-len + 1), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.back_b, -len + 1, 0,
									-len + 1), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.back_c, -len + 1,
									-len + 1, -len + 1), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.back_d, 0, -len + 1,
									-len + 1), len), len, step + 1);
	}
	else
		draw_cube(env, cube);
}

void					fill_cantor(t_env *env)
{
	t_cube	cube;
	t_point	start;

	start.x = -env->fract.len / 2;
	start.y = -env->fract.len / 2;
	start.z = -env->fract.len / 2;
	cube = get_cube(start, env->fract.len);
	cantor_recur(env, cube, env->fract.len, 0);
}
