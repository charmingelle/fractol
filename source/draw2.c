/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 19:56:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_2seg(t_env *env, t_2point start, t_2point end, int color)
{
	double	t;
	double	step;
	int		x;
	int		y;

	step = 1 / sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	t = 0.0;
	while (t <= 1.0)
	{
		x = ROUND((end.x - start.x) * t) + start.x;
		y = ROUND((end.y - start.y) * t) + start.y;
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			env->image_data[y * WIDTH + x] = color;
		t += step;
	}
}

void	draw(t_env *env)
{
	ft_bzero(env->image_data, WIDTH * HEIGHT * 4);
	ft_bzero(env->z_buff, WIDTH * HEIGHT * 8);
	fill_ft_image(env);
	mlx_put_image_to_window(env->mlx, env->wind, env->image, 0, 0);
	mlx_string_put(env->mlx, env->wind, 10, 10, 0xFFFFFF, env->ft.man);
}
