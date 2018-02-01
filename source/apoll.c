/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apoll.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:55:02 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 20:04:19 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		get_circle_outside_all(t_env *env, int lev, t_circle c[3])
{
	t_circle	new;

	new = get_apoll_all(c[0], c[1], c[2]);
	if (new.rad <= 1)
		return ;
	draw_circle(env, new, get_rainbow_color(lev));
	if (lev++ < env->ft.lev)
	{
		get_circle_outside_all(env, lev, (t_circle[3]){c[0], c[1], new});
		get_circle_outside_all(env, lev, (t_circle[3]){c[0], c[2], new});
		get_circle_outside_all(env, lev, (t_circle[3]){c[1], c[2], new});
	}
}

static t_circle	get_apoll_two(t_circle c0, t_circle c1, t_circle c2)
{
	double		a;
	double		b;
	double		c;
	t_circle	apoll;

	a = 1 / c0.rad;
	b = 1 / c1.rad;
	c = -1 / c2.rad;
	apoll.rad = 1 / (a + b + c + 2 * sqrt(a * b + b * c + c * a));
	apoll.center = get_far_center(c0, c1, c2, apoll.rad);
	return (apoll);
}

static void		get_circle_outside_two(t_env *env, int lev, t_circle c[3])
{
	t_circle	new;

	new = get_apoll_two(c[0], c[1], c[2]);
	if (new.rad <= 1)
		return ;
	draw_circle(env, new, get_rainbow_color(lev));
	if (lev++ < env->ft.lev)
	{
		get_circle_outside_two(env, lev, (t_circle[3]){new, c[0], c[2]});
		get_circle_outside_two(env, lev, (t_circle[3]){new, c[1], c[2]});
		get_circle_outside_all(env, lev, (t_circle[3]){c[0], c[1], new});
	}
}

static void		draw_lev_0(t_env *env, t_circle c0, t_circle c1, t_circle c2)
{
	draw_circle(env, c0, get_rainbow_color(1));
	draw_circle(env, c1, get_rainbow_color(1));
	draw_circle(env, c2, get_rainbow_color(1));
}

void			fill_apoll(t_env *env)
{
	t_circle	c0;
	t_circle	c1;
	t_circle	c2;
	double		rad;
	t_circle	big;

	rad = (HEIGHT / 4.46) * env->ft.scale;
	c0 = get_circle(WIDTH / 2 + env->ft.shift.x, rad + env->ft.shift.y, rad);
	c1 = get_circle(WIDTH / 2 - rad + env->ft.shift.x,
					rad + rad * sqrt(3) + env->ft.shift.y, rad);
	c2 = get_circle(WIDTH / 2 + rad + env->ft.shift.x,
					rad + rad * sqrt(3) + env->ft.shift.y, rad);
	big = get_outer_circle(c0, c1, c2);
	draw_circle(env, big, get_rainbow_color(0));
	if (env->ft.lev > 0)
		draw_lev_0(env, c0, c1, c2);
	if (env->ft.lev > 1)
	{
		get_circle_outside_all(env, 2, (t_circle[3]){c0, c1, c2});
		get_circle_outside_two(env, 2, (t_circle[3]){c0, c1, big});
		get_circle_outside_two(env, 2, (t_circle[3]){c1, c2, big});
		get_circle_outside_two(env, 2, (t_circle[3]){c2, c0, big});
	}
}
