#include "header.h"

static void	julia_special_handler(t_env *env)
{
	if (env->juls == 0)
		env->juls = 1;
	else
		env->juls = 0;
}

static void	arrow_left_handler(t_env *env)
{
	int	changed;

	changed = 0;
	if ((env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP) && (changed = 1))
		env->fract.shift.x += env->fract.scale * 10;
	else if (env->fract.number == JULIA && (changed = 1))
		env->fract.pivot.x += env->fract.scale / 20;
	else if (env->fract.number == TREE && (changed = 1))
		env->fract.tilte -= 1;
	changed ? draw(env) : 0;
}

static void	arrow_right_handler(t_env *env)
{
	int	changed;

	changed = 0;
	if ((env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP) && (changed = 1))
		env->fract.shift.x -= env->fract.scale * 10;
	else if (env->fract.number == JULIA && (changed = 1))
		env->fract.pivot.x -= env->fract.scale / 20;
	else if (env->fract.number == TREE && (changed = 1))
		env->fract.tilte += 1;
	changed ? draw(env) : 0;
}

static void	arrow_up_handler(t_env *env)
{
	int	changed;

	changed = 0;
	if ((env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP) && (changed = 1))
		env->fract.shift.y += env->fract.scale * 10;
	else if (env->fract.number == JULIA && (changed = 1))
		env->fract.pivot.y += env->fract.scale / 20;
	else if (env->fract.number == APOLL && env->fract.lev < 7 && (changed = 1))
		env->fract.lev += 1;
	else if ((env->fract.number == SERP || env->fract.number == CANTOR) && env->fract.lev < 5 && (changed = 1))
		env->fract.lev += 1;
	else if (env->fract.number == TREE && (changed = 1))
		env->fract.closeness -= 1;
	changed ? draw(env) : 0;
}

static void	arrow_down_handler(t_env *env)
{
	int	changed;

	changed = 0;
	if ((env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP) && (changed = 1))
		env->fract.shift.y -= env->fract.scale * 10;
	else if (env->fract.number == JULIA && (changed = 1))
		env->fract.pivot.y -= env->fract.scale / 20;
	else if ((env->fract.number == APOLL || env->fract.number == SERP || env->fract.number == CANTOR) && env->fract.lev > 0 && (changed = 1))
		env->fract.lev -= 1;
	else if (env->fract.number == TREE && (changed = 1))
		env->fract.closeness += 1;
	changed ? draw(env) : 0;
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
	int	rotatable;
	int	rotated;

	rotatable = (env->fract.number == CANTOR || env->fract.number == SERP);
	rotated = 0;
	keycode == ESC ? close_wind_handler(env) : 0;
	keycode == J && env->fract.number == JULIA ? julia_special_handler(env) : 0;
	keycode == A && rotatable && (rotated = 1) ? (env->ang_y = (env->ang_y + 5) % 360) : 0;
	keycode == D && rotatable && (rotated = 1) ? (env->ang_y = (env->ang_y - 5) % 360) : 0;
	keycode == W && rotatable && (rotated = 1) ? (env->ang_x = (env->ang_x - 5) % 360) : 0;
	keycode == S && rotatable && (rotated = 1) ? (env->ang_x = (env->ang_x + 5) % 360) : 0;
	keycode == Q && rotatable && (rotated = 1) ? (env->ang_z = (env->ang_z + 5) % 360) : 0;
	keycode == E && rotatable && (rotated = 1) ? (env->ang_z = (env->ang_z - 5) % 360) : 0;
	rotatable && rotated ? draw(env) : 0;
	keycode == ARROW_LEFT ? arrow_left_handler(env) : 0;
	keycode == ARROW_RIGHT ? arrow_right_handler(env) : 0;
	keycode == ARROW_UP ? arrow_up_handler(env) : 0;
	keycode == ARROW_DOWN ? arrow_down_handler(env) : 0;
	return (0);
}

static void	scroll_up_handler(t_env *env, int x, int y)
{
	int	changed;

	changed = 0;
	if ((env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP) && (changed = 1))
	{
		env->fract.scale -= env->fract.scale / SCALE_COEFFICIENT;
		env->fract.shift.x = ft_lerp(env->fract.shift.x,
			env->fract.shift.x + (x - WIDTH / 2.0) * env->fract.scale, 0.07);
		env->fract.shift.y = ft_lerp(env->fract.shift.y,
			env->fract.shift.y + (y - HEIGHT / 2.0) * env->fract.scale, 0.07);
	}
	else if (env->fract.number == JULIA && (changed = 1))
	{
		env->fract.scale += env->fract.scale / SCALE_COEFFICIENT;
		env->fract.pivot.x = ft_lerp(env->fract.pivot.x,
			1.5 * (x - WIDTH / 2) / (0.5 * env->fract.scale * WIDTH) + env->fract.pivot.x, 0.06);
		env->fract.pivot.y = ft_lerp(env->fract.pivot.y,
			(y - HEIGHT / 2) / (0.5 * env->fract.scale * HEIGHT) + env->fract.pivot.y, 0.06);
	}
	else if (env->fract.number == TREE && env->fract.lev < 15 && (changed = 1))
		env->fract.lev += 1;
	changed ? draw(env) : 0;
}

static void	scroll_down_handler(t_env *env, int x, int y)
{
	int	changed;

	x = 0;
	y = 0;
	changed = 0;
	if ((env->fract.number == MANDEL || env->fract.number == TRICORN || env->fract.number == SHIP) && (changed = 1))
		env->fract.scale += env->fract.scale / SCALE_COEFFICIENT;
	else if (env->fract.number == JULIA && (changed = 1))
		env->fract.scale -= env->fract.scale / SCALE_COEFFICIENT;
	else if (env->fract.number == TREE && env->fract.lev > 0 && (changed = 1))
		env->fract.lev -= 1;
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
	if (env->fract.number == JULIA && env->juls)
	{
		env->fract.shift.x = -1.4 * x / WIDTH;
		env->fract.shift.y = 0.5403 * y / HEIGHT;
		draw(env);
	}
	return (0);
}
