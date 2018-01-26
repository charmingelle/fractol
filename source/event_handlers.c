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
	keycode == ARROW_LEFT && (env->fract_type == 1 || env->fract_type == 6 || env->fract_type == 7) ? env->fract.shift.re += env->fract.scale * 10 : 0;
	keycode == ARROW_LEFT && env->fract_type == 2 ? env->fract.pivot.re += env->fract.scale / 20 : 0;
	keycode == ARROW_LEFT && env->fract_type == 9 ? env->fract.tilte -= 1 : 0;
	keycode == ARROW_RIGHT && (env->fract_type == 1 || env->fract_type == 6 || env->fract_type == 7) ? env->fract.shift.re -= env->fract.scale * 10 : 0;
	keycode == ARROW_RIGHT && env->fract_type == 2 ? env->fract.pivot.re -= env->fract.scale / 20 : 0;
	keycode == ARROW_RIGHT && env->fract_type == 9 ? env->fract.tilte += 1 : 0;
	keycode == ARROW_UP && (env->fract_type == 1 || env->fract_type == 6 || env->fract_type == 7) ? env->fract.shift.im += env->fract.scale * 10 : 0;
	keycode == ARROW_UP && env->fract_type == 2 ? env->fract.pivot.im += env->fract.scale / 20 : 0;
	keycode == ARROW_UP && (env->fract_type == 4 || env->fract_type == 5 || env->fract_type == 8) && env->fract.lev < 7 ? env->fract.lev += 1 : 0;
	// printf("env->fract.lev = %d\n", env->fract.lev);
	keycode == ARROW_UP && env->fract_type == 9 ? env->fract.closeness -= 1 : 0;
	keycode == ARROW_DOWN && (env->fract_type == 1 || env->fract_type == 6 || env->fract_type == 7) ? env->fract.shift.im -= env->fract.scale * 10 : 0;
	keycode == ARROW_DOWN && env->fract_type == 2 ? env->fract.pivot.im -= env->fract.scale / 20 : 0;
	keycode == ARROW_DOWN && (env->fract_type == 4 || env->fract_type == 5 || env->fract_type == 8) && env->fract.lev > 0 ? env->fract.lev -= 1 : 0;
	keycode == ARROW_DOWN && env->fract_type == 9 ? env->fract.closeness += 1 : 0;
	draw(env);
	return (0);
}

double	ft_lerp(double a, double b, double t)
{
	return ((1.0 - t) * a + b * t);
}

int	mouse_handler(int button, int x, int y, t_env *env)
{
	if (button == 4 && (env->fract_type == 1 || env->fract_type == 6 || env->fract_type == 7))
	{
		env->fract.scale -= env->fract.scale / SCALE_COEFFICIENT;
		env->fract.shift.re = ft_lerp(env->fract.shift.re,
			env->fract.shift.re + (x - WIDTH / 2.0) * env->fract.scale, 0.07);
		env->fract.shift.im = ft_lerp(env->fract.shift.im,
			env->fract.shift.im + (y - HEIGHT / 2.0) * env->fract.scale, 0.07);
		draw(env);
	}
	if (button == 5 && (env->fract_type == 1 || env->fract_type == 6 || env->fract_type == 7))
	{
		env->fract.scale += env->fract.scale / SCALE_COEFFICIENT;
		draw(env);
	}
	if (button == 4 && env->fract_type == 2)
	{
		env->fract.scale += env->fract.scale / SCALE_COEFFICIENT;
		env->fract.pivot.re = ft_lerp(env->fract.pivot.re,
			1.5 * (x - WIDTH / 2) / (0.5 * env->fract.scale * WIDTH) + env->fract.pivot.re, 0.06);
		env->fract.pivot.im = ft_lerp(env->fract.pivot.im,
			(y - HEIGHT / 2) / (0.5 * env->fract.scale * HEIGHT) + env->fract.pivot.im, 0.06);
		draw(env);
	}
	if (button == 4 && env->fract_type == 9 && env->fract.lev < 15)
	{
		env->fract.lev += 1;
		draw(env);
	}
	if (button == 5 && env->fract_type == 2)
	{
		env->fract.scale -= env->fract.scale / SCALE_COEFFICIENT;
		draw(env);
	}
	if (button == 5 && env->fract_type == 9 && env->fract.lev > 0)
	{
		env->fract.lev -= 1;
		draw(env);
	}
	return (0);
}

int	mouse_move_handler(int x, int y, t_env *env)
{
	if (env->fract_type == 2)
	{
		env->fract.shift.re = -1.4 * x / WIDTH;
		env->fract.shift.im = 0.5403 * y / HEIGHT;
		draw(env);
	}
	return (0);
}
