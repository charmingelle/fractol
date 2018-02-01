/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:20 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 19:56:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int			mouse_handler(int button, int x, int y, t_env *env)
{
	button == SCROLL_UP ? scroll_up_handler(env, x, y) : 0;
	button == SCROLL_DOWN ? scroll_down_handler(env, x, y) : 0;
	return (0);
}

int			mouse_move_handler(int x, int y, t_env *env)
{
	if (env->ft.number == JULIA && env->juls_dance)
	{
		env->ft.shift.x = -1.4 * x / WIDTH;
		env->ft.shift.y = 0.5403 * y / HEIGHT;
		draw(env);
	}
	return (0);
}
