/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:34 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 19:56:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_ft	get_mandel(void)
{
	t_ft	ft;

	ft.number = MANDEL;
	ft.scale = 0.005;
	ft.shift.x = 0;
	ft.shift.y = 0;
	ft.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale";
	ft.file = "./cl/mandel.cl";
	return (ft);
}

t_ft	get_julia(void)
{
	t_ft	ft;

	ft.number = JULIA;
	ft.scale = 1;
	ft.shift.x = -0.7;
	ft.shift.y = 0.27015;
	ft.pivot.x = 0.0;
	ft.pivot.y = 0.0;
	ft.man = "LEFT, RIGHT, UP, DOWN - move     \
		SCROLL - change scale     \
		J - Julia dancing mode :)";
	ft.file = "./cl/julia.cl";
	return (ft);
}

t_ft	get_ship(void)
{
	t_ft	ft;

	ft.number = SHIP;
	ft.scale = 0.005;
	ft.shift.x = 0;
	ft.shift.y = 0;
	ft.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale";
	ft.file = "./cl/ship.cl";
	return (ft);
}

t_ft	get_tricorn(void)
{
	t_ft	ft;

	ft.number = TRICORN;
	ft.scale = 0.005;
	ft.shift.x = 0;
	ft.shift.y = 0;
	ft.pivot.x = 0.0;
	ft.pivot.y = 0.0;
	ft.man = "LEFT, RIGHT, UP, DOWN - move     SCROLL - change scale";
	ft.file = "./cl/tricorn.cl";
	return (ft);
}
