#include "header.h"

double	degree_to_rad(int degree)
{
	return (((double)degree * M_PI) / 180.0);
}

void	draw_line(t_env *env, int x_start, int y_start, int x_end, int y_end)
{
	double	t;
	double	step;
	int		x;
	int		y;

	step = 1 / sqrt(pow(x_start - x_end, 2) + pow(y_start - y_end, 2));
	t = 0.0;
	while (t <= 1.0)
	{
		x = (x_end - x_start) * t + x_start;
		y = (y_end - y_start) * t + y_start;
		env->image_data[y * WIDTH + x] = WHITE;
		t += step;
	}
}

void	draw_circle(t_env *env, t_circle circle)
{
	int		x;
	int		y;
	int		x_prev;
	int		y_prev;
	double	phi;
	double	step;

	step = 0.01;
	phi = 0.0;
	x_prev = 0;
	y_prev = 0;
	while (phi < 361.0)
	{
		x = circle.rad * cos(degree_to_rad(phi)) + circle.center.x;
		y = circle.rad * sin(degree_to_rad(phi)) + circle.center.y;
		if (x_prev != 0 && y_prev != 0)
			draw_line(env, x_prev, y_prev, x, y);
		env->image_data[y * WIDTH + x] = WHITE;
		phi += step;
		x_prev = x;
		y_prev = y;
	}
}
