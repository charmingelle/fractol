/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:43 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 19:56:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_point	get_middle(t_point a, t_point b)
{
	t_point	middle;

	middle.x = (a.x + b.x) / 2;
	middle.y = (a.y + b.y) / 2;
	middle.z = (a.z + b.z) / 2;
	return (middle);
}

static t_pyr	get_pyr(t_point top, t_point a, t_point b, t_point c)
{
	t_pyr	pyr;

	pyr.top = top;
	pyr.a = a;
	pyr.b = b;
	pyr.c = c;
	return (pyr);
}

static void		draw_pyr(t_env *env, t_pyr pyr)
{
	draw_triang(env, (t_point[3]){pyr.top, pyr.a, pyr.b}, 0xFF0000);
	draw_triang(env, (t_point[3]){pyr.top, pyr.b, pyr.c}, 0xFF7F00);
	draw_triang(env, (t_point[3]){pyr.top, pyr.c, pyr.a}, 0xFFFF00);
	draw_triang(env, (t_point[3]){pyr.a, pyr.b, pyr.c}, 0x00FF00);
}

static void		serp_recur(t_env *env, t_pyr pyr, int lev)
{
	t_point	mids[6];

	mids[0] = get_middle(pyr.top, pyr.a);
	mids[1] = get_middle(pyr.top, pyr.b);
	mids[2] = get_middle(pyr.top, pyr.c);
	mids[3] = get_middle(pyr.a, pyr.b);
	mids[4] = get_middle(pyr.b, pyr.c);
	mids[5] = get_middle(pyr.c, pyr.a);
	if (lev < env->ft.lev)
	{
		serp_recur(env, get_pyr(pyr.top, mids[0], mids[1], mids[2]), lev + 1);
		serp_recur(env, get_pyr(mids[0], pyr.a, mids[3], mids[5]), lev + 1);
		serp_recur(env, get_pyr(mids[1], mids[3], pyr.b, mids[4]), lev + 1);
		serp_recur(env, get_pyr(mids[2], mids[5], mids[4], pyr.c), lev + 1);
	}
	else
		draw_pyr(env, pyr);
}

void			fill_serp(t_env *env)
{
	int		step;
	double	part;

	part = sqrt(3) * env->ft.len / 6;
	step = 0;
	serp_recur(env, get_pyr((t_point){0, -2 * part, 0},
		(t_point){-env->ft.len / 2, part, part},
		(t_point){env->ft.len / 2, part, part},
		(t_point){0, part, -2 * part}),
		step);
}
