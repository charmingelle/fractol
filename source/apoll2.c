/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apoll2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:55:47 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 19:55:51 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_2point		get_far_center(t_circle c0, t_circle c1, t_circle outer,
	double small_rad)
{
	t_2point	first;
	t_2point	second;
	double		d;
	double		a;
	double		h;

	d = sqrt(pow(c0.center.x - c1.center.x, 2)
		+ pow(c0.center.y - c1.center.y, 2));
	a = ((c0.rad + small_rad) * (c0.rad + small_rad)
		- (c1.rad + small_rad) * (c1.rad + small_rad) + d * d) / (2 * d);
	h = sqrt(pow(c0.rad + small_rad, 2) - pow(a, 2));
	first.x = c0.center.x + a * (c1.center.x - c0.center.x)
		/ d + h * (c1.center.y - c0.center.y) / d;
	first.y = c0.center.y + a * (c1.center.y - c0.center.y)
		/ d - h * (c1.center.x - c0.center.x) / d;
	second.x = c0.center.x + a * (c1.center.x - c0.center.x)
		/ d - h * (c1.center.y - c0.center.y) / d;
	second.y = c0.center.y + a * (c1.center.y - c0.center.y)
		/ d + h * (c1.center.x - c0.center.x) / d;
	if (get_2dist(first, outer.center) > get_2dist(second, outer.center))
		return (first);
	return (second);
}

static t_2point	get_close_center(t_circle c0, t_circle c1, t_circle outer,
	double small_rad)
{
	t_2point	first;
	t_2point	second;
	double		d;
	double		a;
	double		h;

	d = sqrt(pow(c0.center.x - c1.center.x, 2)
		+ pow(c0.center.y - c1.center.y, 2));
	a = ((c0.rad + small_rad) * (c0.rad + small_rad)
		- (c1.rad + small_rad) * (c1.rad + small_rad) + d * d) / (2 * d);
	h = sqrt(pow(c0.rad + small_rad, 2) - pow(a, 2));
	first.x = c0.center.x + a * (c1.center.x - c0.center.x)
		/ d + h * (c1.center.y - c0.center.y) / d;
	first.y = c0.center.y + a * (c1.center.y - c0.center.y)
		/ d - h * (c1.center.x - c0.center.x) / d;
	second.x = c0.center.x + a * (c1.center.x - c0.center.x)
		/ d - h * (c1.center.y - c0.center.y) / d;
	second.y = c0.center.y + a * (c1.center.y - c0.center.y)
		/ d + h * (c1.center.x - c0.center.x) / d;
	if (get_2dist(first, outer.center) < get_2dist(second, outer.center))
		return (first);
	return (second);
}

static t_2point	get_outer_center(t_2point a, t_2point b, t_2point c)
{
	t_2point	center;
	double		s1;
	double		s2;
	double		s3;

	s1 = get_2dist(a, b);
	s2 = get_2dist(b, c);
	s3 = get_2dist(c, a);
	center.x = (s1 * a.x + s2 * b.x + s3 * c.x) / (s1 + s2 + s3);
	center.y = (s1 * a.y + s2 * b.y + s3 * c.y) / (s1 + s2 + s3);
	return (center);
}

t_circle		get_outer_circle(t_circle c0, t_circle c1, t_circle c2)
{
	double		a;
	double		b;
	double		c;
	t_circle	apoll;

	a = -1 / c0.rad;
	b = -1 / c1.rad;
	c = -1 / c2.rad;
	apoll.rad = 1 / (a + b + c + 2 * sqrt(a * b + b * c + c * a));
	apoll.center = get_outer_center(c0.center, c1.center, c2.center);
	return (apoll);
}

t_circle		get_apoll_all(t_circle c0, t_circle c1, t_circle c2)
{
	double		a;
	double		b;
	double		c;
	t_circle	apoll;

	a = 1 / c0.rad;
	b = 1 / c1.rad;
	c = 1 / c2.rad;
	apoll.rad = 1 / (a + b + c + 2 * sqrt(a * b + b * c + c * a));
	apoll.center = get_close_center(c0, c1, c2, apoll.rad);
	return (apoll);
}
