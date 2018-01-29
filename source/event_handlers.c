#include "../includes/header.h"

void	arrow_left_handler(t_env *env)
{
	if (env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP)
		env->fract.shift.re += env->fract.scale * 10;
	else if (env->fract.number == JULIA)
		env->fract.pivot.re += env->fract.scale / 20;
	else if (env->fract.number == TREE)
		env->fract.tilte -= 1;
}

void	arrow_right_handler(t_env *env)
{
	if (env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP)
		env->fract.shift.re -= env->fract.scale * 10;
	else if (env->fract.number == JULIA)
		env->fract.pivot.re -= env->fract.scale / 20;
	else if (env->fract.number == TREE)
		env->fract.tilte += 1;
}

void	arrow_up_handler(t_env *env)
{
	if (env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP)
		env->fract.shift.im += env->fract.scale * 10;
	else if (env->fract.number == JULIA)
		env->fract.pivot.im += env->fract.scale / 20;
	else if ((env->fract.number == APOLL || env->fract.number == SERP || env->fract.number == CANTOR) && env->fract.lev < 7)
		env->fract.lev += 1;
	else if (env->fract.number == TREE)
		env->fract.closeness -= 1;
}

void	arrow_down_handler(t_env *env)
{
	if (env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP)
		env->fract.shift.im -= env->fract.scale * 10;
	else if (env->fract.number == JULIA)
		env->fract.pivot.im -= env->fract.scale / 20;
	else if ((env->fract.number == APOLL || env->fract.number == SERP || env->fract.number == CANTOR) && env->fract.lev > 0)
		env->fract.lev -= 1;
	else if (env->fract.number == TREE)
		env->fract.closeness += 1;
}

int		key_handler(int keycode, t_env *env)
{
	int	needed_key;

	needed_key = 0;
	keycode == ESC && (needed_key = 1) ? exit(0) : 0;
	keycode == A && (needed_key = 1) ? (env->ang_y = (env->ang_y + 5) % 360) : 0;
	keycode == D && (needed_key = 1) ? (env->ang_y = (env->ang_y - 5) % 360) : 0;
	keycode == W && (needed_key = 1) ? (env->ang_x = (env->ang_x - 5) % 360) : 0;
	keycode == S && (needed_key = 1) ? (env->ang_x = (env->ang_x + 5) % 360) : 0;
	keycode == Q && (needed_key = 1) ? (env->ang_z = (env->ang_z + 5) % 360) : 0;
	keycode == E && (needed_key = 1) ? (env->ang_z = (env->ang_z - 5) % 360) : 0;
	keycode == ARROW_LEFT && (needed_key = 1) ? arrow_left_handler(env) : 0;
	keycode == ARROW_RIGHT && (needed_key = 1) ? arrow_right_handler(env) : 0;
	keycode == ARROW_UP && (needed_key = 1) ? arrow_up_handler(env) : 0;
	keycode == ARROW_DOWN && (needed_key = 1) ? arrow_down_handler(env) : 0;
	needed_key == 1 ? draw(env) : 0;
	return (0);
}

void	scroll_up_handler(t_env *env, int x, int y)
{
	if (env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP)
	{
		env->fract.scale -= env->fract.scale / SCALE_COEFFICIENT;
		env->fract.shift.re = ft_lerp(env->fract.shift.re,
			env->fract.shift.re + (x - WIDTH / 2.0) * env->fract.scale, 0.07);
		env->fract.shift.im = ft_lerp(env->fract.shift.im,
			env->fract.shift.im + (y - HEIGHT / 2.0) * env->fract.scale, 0.07);
	}
	else if (env->fract.number == JULIA)
	{
		env->fract.scale += env->fract.scale / SCALE_COEFFICIENT;
		env->fract.pivot.re = ft_lerp(env->fract.pivot.re,
			1.5 * (x - WIDTH / 2) / (0.5 * env->fract.scale * WIDTH) + env->fract.pivot.re, 0.06);
		env->fract.pivot.im = ft_lerp(env->fract.pivot.im,
			(y - HEIGHT / 2) / (0.5 * env->fract.scale * HEIGHT) + env->fract.pivot.im, 0.06);
	}
	else if (env->fract.number == TREE && env->fract.lev < 15)
		env->fract.lev += 1;
}

void	scroll_down_handler(t_env *env, int x, int y)
{
	if (env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP)
		env->fract.scale += env->fract.scale / SCALE_COEFFICIENT;
	else if (env->fract.number == JULIA)
		env->fract.scale -= env->fract.scale / SCALE_COEFFICIENT;
	else if (env->fract.number == TREE && env->fract.lev > 0)
		env->fract.lev -= 1;
}

int		mouse_handler(int button, int x, int y, t_env *env)
{
	int	needed_button;

	needed_button = 0;
	button == 4 && (needed_button = 1) ? scroll_up_handler(env, x, y) : 0;
	button == 5 && (needed_button = 1) ? scroll_down_handler(env, x, y) : 0;
	needed_button == 1 ? draw(env) : 0;
	return (0);
}

int		mouse_move_handler(int x, int y, t_env *env)
{
	if (env->fract.number == JULIA)
	{
		env->fract.shift.re = -1.4 * x / WIDTH;
		env->fract.shift.im = 0.5403 * y / HEIGHT;
		draw(env);
	}
	return (0);
}
