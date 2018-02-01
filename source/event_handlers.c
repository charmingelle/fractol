#include "header.h"

static void	julia_special_handler(t_env *env)
{
	if (env->juls_dance == 0)
		env->juls_dance = 1;
	else
		env->juls_dance = 0;
}

static void	arrow_left_handler(t_env *env)
{
	int	changed;

	changed = 0;
	if ((env->ft.number == MANDEL || env->ft.number == TRICORN
		|| env->ft.number == SHIP) && (changed = 1))
		env->ft.shift.x += env->ft.scale * 10;
	else if (env->ft.number == JULIA && (changed = 1))
		env->ft.pivot.x += env->ft.scale / 20;
	else if (env->ft.number == APOLL && (changed = 1))
		env->ft.shift.x -= env->ft.scale * 10;
	else if (env->ft.number == TREE && (changed = 1))
		env->ft.tilte -= 1;
	changed ? draw(env) : 0;
}

static void	arrow_right_handler(t_env *env)
{
	int	changed;

	changed = 0;
	if ((env->ft.number == MANDEL || env->ft.number == TRICORN
		|| env->ft.number == SHIP) && (changed = 1))
		env->ft.shift.x -= env->ft.scale * 10;
	else if (env->ft.number == JULIA && (changed = 1))
		env->ft.pivot.x -= env->ft.scale / 20;
	else if (env->ft.number == APOLL && (changed = 1))
		env->ft.shift.x += env->ft.scale * 10;
	else if (env->ft.number == TREE && (changed = 1))
		env->ft.tilte += 1;
	changed ? draw(env) : 0;
}

static void	arrow_up_handler(t_env *env)
{
	int	changed;

	changed = 0;
	if ((env->ft.number == MANDEL || env->ft.number == TRICORN
		|| env->ft.number == SHIP) && (changed = 1))
		env->ft.shift.y += env->ft.scale * 10;
	else if (env->ft.number == JULIA && (changed = 1))
		env->ft.pivot.y += env->ft.scale / 20;
	else if (env->ft.number == APOLL && (changed = 1))
		env->ft.shift.y -= env->ft.scale * 10;
	else if ((env->ft.number == SERP || env->ft.number == CANTOR)
		&& env->ft.lev < 5 && (changed = 1))
		env->ft.lev += 1;
	else if (env->ft.number == TREE && (changed = 1))
		env->ft.close -= 1;
	changed ? draw(env) : 0;
}

static void	arrow_down_handler(t_env *env)
{
	int	changed;

	changed = 0;
	if ((env->ft.number == MANDEL || env->ft.number == TRICORN
		|| env->ft.number == SHIP) && (changed = 1))
		env->ft.shift.y -= env->ft.scale * 10;
	else if (env->ft.number == JULIA && (changed = 1))
		env->ft.pivot.y -= env->ft.scale / 20;
	else if (env->ft.number == APOLL && (changed = 1))
		env->ft.shift.y += env->ft.scale * 10;
	else if ((env->ft.number == SERP || env->ft.number == CANTOR)
		&& env->ft.lev > 0 && (changed = 1))
		env->ft.lev -= 1;
	else if (env->ft.number == TREE && (changed = 1))
		env->ft.close += 1;
	changed ? draw(env) : 0;
}

void	plus_handler(t_env *env)
{
	if (env->ft.number == APOLL)
	{
		env->ft.lev += 1;
		env->ft.lev > 10 ? (env->ft.scale += 0.1) : 0;
		draw(env);
	}
}

void	minus_handler(t_env *env)
{
	if (env->ft.number == APOLL)
	{
		env->ft.lev > 0 ? env->ft.lev -= 1 : 0;
		env->ft.lev >= 10 ? (env->ft.scale -= 0.1) : 0;
		draw(env);
	}
}

int		close_wind_handler(t_env *env)
{
	mlx_destroy_window(env->mlx, env->wind);
	*(env->wind_amount) -= 1;
	if (*env->wind_amount == 0)
		exit(0);
	return (0);
}

int		key_handler(int keycode, t_env *env)
{
	int	rotated;

	rotated = 0;
	keycode == ESC ? close_wind_handler(env) : 0;
	keycode == J && env->ft.number == JULIA ? julia_special_handler(env) : 0;
	if (keycode == A && (rotated = 1))
		(env->ang_y = (env->ang_y + 5) % 360);
	if (keycode == D && (rotated = 1))
		(env->ang_y = (env->ang_y - 5) % 360);
	if (keycode == W && (rotated = 1))
		(env->ang_x = (env->ang_x - 5) % 360);
	if (keycode == S && (rotated = 1))
		(env->ang_x = (env->ang_x + 5) % 360);
	if (keycode == Q && (rotated = 1))
		(env->ang_z = (env->ang_z + 5) % 360);
	if (keycode == E && (rotated = 1))
		(env->ang_z = (env->ang_z - 5) % 360);
	rotated ? draw(env) : 0;
	keycode == ARROW_LEFT ? arrow_left_handler(env) : 0;
	keycode == ARROW_RIGHT ? arrow_right_handler(env) : 0;
	keycode == ARROW_UP ? arrow_up_handler(env) : 0;
	keycode == ARROW_DOWN ? arrow_down_handler(env) : 0;
	keycode == PLUS ? plus_handler(env) : 0;
	keycode == MINUS ? minus_handler(env) : 0;
	return (0);
}

static void	scroll_up_handler(t_env *env, int x, int y)
{
	int	changed;

	changed = 0;
	if ((env->ft.number == MANDEL || env->ft.number == TRICORN
		|| env->ft.number == SHIP) && (changed = 1))
	{
		env->ft.scale -= env->ft.scale / SCALE_COEFFICIENT;
		env->ft.shift.x = ft_lerp(env->ft.shift.x,
			env->ft.shift.x + (x - WIDTH / 2.0) * env->ft.scale, 0.07);
		env->ft.shift.y = ft_lerp(env->ft.shift.y,
			env->ft.shift.y + (y - HEIGHT / 2.0) * env->ft.scale, 0.07);
	}
	else if (env->ft.number == JULIA && (changed = 1))
	{
		env->ft.scale += env->ft.scale / SCALE_COEFFICIENT;
		env->ft.pivot.x = ft_lerp(env->ft.pivot.x,
			1.5 * (x - WIDTH / 2) / (0.5 * env->ft.scale * WIDTH)
			+ env->ft.pivot.x, 0.06);
		env->ft.pivot.y = ft_lerp(env->ft.pivot.y,
			(y - HEIGHT / 2) / (0.5 * env->ft.scale * HEIGHT)
			+ env->ft.pivot.y, 0.06);
	}
	else if (env->ft.number == TREE && env->ft.lev < 15 && (changed = 1))
		env->ft.lev += 1;
	changed ? draw(env) : 0;
}

static void	scroll_down_handler(t_env *env, int x, int y)
{
	int	changed;

	x = 0;
	y = 0;
	changed = 0;
	if ((env->ft.number == MANDEL || env->ft.number == TRICORN
		|| env->ft.number == SHIP) && (changed = 1))
		env->ft.scale += env->ft.scale / SCALE_COEFFICIENT;
	else if (env->ft.number == JULIA && (changed = 1))
		env->ft.scale -= env->ft.scale / SCALE_COEFFICIENT;
	else if (env->ft.number == TREE && env->ft.lev > 0 && (changed = 1))
		env->ft.lev -= 1;
	changed ? draw(env) : 0;
}

int		mouse_handler(int button, int x, int y, t_env *env)
{
	button == SCROLL_UP ? scroll_up_handler(env, x, y) : 0;
	button == SCROLL_DOWN ? scroll_down_handler(env, x, y) : 0;
	return (0);
}

int		mouse_move_handler(int x, int y, t_env *env)
{
	if (env->ft.number == JULIA && env->juls_dance)
	{
		env->ft.shift.x = -1.4 * x / WIDTH;
		env->ft.shift.y = 0.5403 * y / HEIGHT;
		draw(env);
	}
	return (0);
}
