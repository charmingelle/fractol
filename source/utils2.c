/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:53 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 20:21:56 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double		ft_lerp(double a, double b, double t)
{
	return ((1.0 - t) * a + b * t);
}

void		validate_ft(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 8)
			exit(show_usage_error());
}

t_circle	get_circle(double center_x, double center_y, double rad)
{
	t_circle	circle;

	circle.center.x = center_x;
	circle.center.y = center_y;
	circle.rad = rad;
	return (circle);
}

t_point		get_modified_point(t_env *env, t_point point)
{
	t_point p0;
	t_point p1;
	t_point rotated;

	p0.x = point.x;
	p0.y = (point.y * cos(dg_to_rd(env->ang_x)) + point.z
		* sin(dg_to_rd(env->ang_x)));
	p0.z = (point.z * cos(dg_to_rd(env->ang_x)) - point.y
		* sin(dg_to_rd(env->ang_x)));
	p1.x = p0.x * cos(dg_to_rd(env->ang_y)) - p0.z
		* sin(dg_to_rd(env->ang_y));
	p1.y = p0.y;
	p1.z = p0.z * cos(dg_to_rd(env->ang_y)) + p0.x
		* sin(dg_to_rd(env->ang_y));
	rotated.x = (p1.x * cos(dg_to_rd(env->ang_z)) + p1.y
		* sin(dg_to_rd(env->ang_z))) + (WIDTH / 2);
	rotated.y = (p1.y * cos(dg_to_rd(env->ang_z)) - p1.x
		* sin(dg_to_rd(env->ang_z))) + (HEIGHT / 2);
	rotated.z = p1.z;
	return (rotated);
}
