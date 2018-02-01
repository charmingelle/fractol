/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:24 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 19:56:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int			key_handler(int keycode, t_env *env)
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
