#include "header.h"

static void	draw_seg(t_env *env, t_point a, t_point b,
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
		if ((mid.x >= 0 && mid.x < WIDTH && mid.y >= 0 && mid.y < HEIGHT)
			&& (env->z_buff[pos] == 0 || env->z_buff[pos] < mid.z))
		{
			env->z_buff[pos] = mid.z;
			env->image_data[pos] = color;
		}
		t += step;
	}
}

void	draw_parallelogram(t_env *env, t_point a[2],
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

void	draw_cube(t_env *env, t_cube cube)
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

void	draw_2seg(t_env *env, t_2point start, t_2point end, int color)
{
	double	t;
	double	step;
	int		x;
	int		y;

	step = 1 / sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	t = 0.0;
	while (t <= 1.0)
	{
		x = ROUND((end.x - start.x) * t) + start.x;
		y = ROUND((end.y - start.y) * t) + start.y;
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			env->image_data[y * WIDTH + x] = color;
		t += step;
	}
}

void	draw_circle(t_env *env, t_circle circle, int color)
{
	int		x;
	int		y;
	double	phi;
	double	step;

	step = 1.0 / (2.0 * M_PI * circle.rad);
	phi = 0.0;
	while (phi <= 360.0)
	{
		x = ROUND(circle.rad * cos(degree_to_rad(phi)) + circle.center.x);
		y = ROUND(circle.rad * sin(degree_to_rad(phi)) + circle.center.y);
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			env->image_data[y * WIDTH + x] = color;
		phi += step;
	}
}

void	draw_triang(t_env *env, t_point p[3], int color)
{
	t_point	temp1;
	t_point	temp2;
	double	t;
	double	step;

	step = 0.5 / get_dist(p[2], p[0]);
	t = 0;
	while (t <= 1)
	{
		temp1.x = (p[1].x - p[2].x) * t + p[2].x;
		temp1.y = (p[1].y - p[2].y) * t + p[2].y;
		temp1.z = (p[1].z - p[2].z) * t + p[2].z;
		temp2.x = (p[0].x - p[2].x) * t + p[2].x;
		temp2.y = (p[0].y - p[2].y) * t + p[2].y;
		temp2.z = (p[0].z - p[2].z) * t + p[2].z;
		draw_seg(env, temp1, temp2, color);
		t += step;
	}
}
