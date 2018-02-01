/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:28 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 19:56:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	julia_special_handler(t_env *env)
{
	if (env->juls_dance == 0)
		env->juls_dance = 1;
	else
		env->juls_dance = 0;
}

void	plus_handler(t_env *env)
{
	if (env->ft.number == APOLL)
	{
		env->ft.lev += 1;
		env->ft.lev > 10 ? (env->ft.scale += 0.1) : 0;
		draw(env);
	}
}

void	minus_handler(t_env *env)
{
	if (env->ft.number == APOLL)
	{
		env->ft.lev > 0 ? env->ft.lev -= 1 : 0;
		env->ft.lev >= 10 ? (env->ft.scale -= 0.1) : 0;
		draw(env);
	}
}

int		close_wind_handler(t_env *env)
{
	mlx_destroy_window(env->mlx, env->wind);
	*(env->wind_amount) -= 1;
	if (*env->wind_amount == 0)
		exit(0);
	return (0);
}
