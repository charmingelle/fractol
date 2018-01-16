#include "header.h"

int	key_handler(int keycode, t_env *env)
{
	keycode == ESC ? exit(0) : 0;
	keycode == A ? (env->ang_y = (env->ang_y + 5) % 360) : 0;
	keycode == D ? (env->ang_y = (env->ang_y - 5) % 360) : 0;
	keycode == W ? (env->ang_x = (env->ang_x - 5) % 360) : 0;
	keycode == S ? (env->ang_x = (env->ang_x + 5) % 360) : 0;
	keycode == Q ? (env->ang_z = (env->ang_z + 5) % 360) : 0;
	keycode == E ? (env->ang_z = (env->ang_z - 5) % 360) : 0;
	// keycode == ARROW_LEFT ? env->fract.shift.re += env->fract.scale : 0;
	// keycode == ARROW_RIGHT ? env->fract.shift.re -= env->fract.scale : 0;
	// keycode == ARROW_UP ? env->fract.shift.im += env->fract.scale : 0;
	// keycode == ARROW_DOWN ? env->fract.shift.im -= env->fract.scale : 0;
	draw(env);
	return (0);
}

double	ft_lerp(double a, double b, double t)
{
	return ((1.0 - t) * a + b * t);
}

int	mouse_handler(int button, int x, int y, t_env *env)
{
	if (button == 4 && env->fract_type == 1)
	{
		env->fract.scale -= env->fract.scale / SCALE_COEFFICIENT;
		env->fract.shift.re = ft_lerp(env->fract.shift.re,
			env->fract.shift.re + (x - env->width / 2.0) * env->fract.scale, 0.07);
		env->fract.shift.im = ft_lerp(env->fract.shift.im,
			env->fract.shift.im + (y - env->height / 2.0) * env->fract.scale, 0.07);
		draw(env);
	}
	if (button == 5 && env->fract_type == 1)
	{
		env->fract.scale += env->fract.scale / SCALE_COEFFICIENT;
		// env->fract.shift.re -= env->fract.scale;
		// env->fract.shift.im -= env->fract.scale;
		draw(env);
	}
	if (button == 4 && env->fract_type == 2)
	{
		env->fract.scale += env->fract.scale / SCALE_COEFFICIENT;
		draw(env);
	}
	if (button == 5 && env->fract_type == 2)
	{
		env->fract.scale -= env->fract.scale / SCALE_COEFFICIENT;
		draw(env);
	}
	return (0);
}

int	mouse_move_handler(int x, int y, t_env *env)
{
	if (env->fract_type == 2)
	{
		env->fract.shift.re = -1.4 * x / env->width;
		env->fract.shift.im = 0.5403 * y / env->height;
		draw(env);
	}
	return (0);
}
