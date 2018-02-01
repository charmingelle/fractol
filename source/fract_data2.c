/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_data2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:38 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 19:56:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_ft	get_apoll(void)
{
	t_ft	ft;

	ft.number = APOLL;
	ft.scale = 1.0;
	ft.shift.x = 0.0;
	ft.shift.y = 0.0;
	ft.lev = 0;
	ft.man = "PLUS, MINUS - change number of circles     \
		LEFT, RIGHT, UP, DOWN - move";
	return (ft);
}

static t_ft	get_tree(void)
{
	t_ft	ft;

	ft.number = TREE;
	ft.lev = 0;
	ft.tilte = 0;
	ft.close = 45;
	ft.man = "SCROLL - change number of branches     \
		LEFT, RIGHT - bend branches     \
		UP, DOWN - change branch close";
	return (ft);
}

static t_ft	get_cantor(void)
{
	t_ft	ft;

	ft.number = CANTOR;
	ft.lev = 0;
	ft.len = MIN(WIDTH, HEIGHT) / 2;
	ft.man = "UP, DOWN - change number of cubes     W, A, S, D, Q, E - rotate";
	return (ft);
}

static t_ft	get_serp(void)
{
	t_ft	ft;

	ft.number = SERP;
	ft.lev = 0;
	ft.len = MIN(WIDTH, HEIGHT) / 1.3;
	ft.man = "UP, DOWN - change number of pyramids     \
		W, A, S, D, Q, E - rotate";
	return (ft);
}

t_ft		get_ft_data(int number)
{
	t_ft	ft;

	if (number == MANDEL)
		return (get_mandel());
	if (number == JULIA)
		return (get_julia());
	if (number == SHIP)
		return (get_ship());
	if (number == TRICORN)
		return (get_tricorn());
	if (number == APOLL)
		return (get_apoll());
	if (number == TREE)
		return (get_tree());
	if (number == CANTOR)
		return (get_cantor());
	if (number == SERP)
		return (get_serp());
	ft.number = -1;
	return (ft);
}
