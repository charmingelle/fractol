#include "header.h"

int	key_handler(int keycode, t_env *env)
{
	keycode == ESC ? exit(0) : 0;
	keycode == ARROW_LEFT ? env->center.re += env->scale : 0;
	keycode == ARROW_RIGHT ? env->center.re -= env->scale : 0;
	keycode == ARROW_UP ? env->center.im += env->scale : 0;
	keycode == ARROW_DOWN ? env->center.im -= env->scale : 0;
	draw(env);
	return (0);
}

double	ft_lerp(double a, double b, double t)
{
	return ((1.0 - t) * a + b * t);
}

int	mouse_handler(int button, int x, int y, t_env *env)
{
	if (button == 4)
	{
		env->scale -= env->scale / SCALE_COEFFICIENT;
		env->center.re = ft_lerp(env->center.re,
			env->center.re + (x - env->width / 2.0) * env->scale, 0.07);
		env->center.im = ft_lerp(env->center.im,
			env->center.im + (y - env->height / 2.0) * env->scale, 0.07);
		draw(env);
	}
	if (button == 5)
	{
		env->scale += env->scale / SCALE_COEFFICIENT;
		env->center.re -= env->scale;
		env->center.im -= env->scale;
		draw(env);
	}
	return (0);
}
