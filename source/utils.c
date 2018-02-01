/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:50 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 20:04:19 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	dg_to_rd(double degree)
{
	return ((degree * M_PI) / 180.0);
}

double	get_2dist(t_2point a, t_2point b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

double	get_dist(t_point a, t_point b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x)
		+ (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)));
}

int		get_rainbow_color(int i)
{
	static int palette[] = {
		0xFF0000,
		0xFF7F00,
		0xFFFF00,
		0x00FF00,
		0x38EEFF,
		0x0000FF,
		0x9400D3
	};

	return (palette[i % 7]);
}
