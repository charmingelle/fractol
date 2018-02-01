#include "header.h"

static void	tree_recur(t_env *env, t_2point params[2], double len, int lev)
{
	t_2point	new_params[2];

	if (lev < 0 || len < 1)
		return ;
	new_params[0].x = params[0].x + len * params[1].x;
	new_params[0].y = params[0].y + len * params[1].y;
	draw_2seg(env, params[0], new_params[0], get_mid_color(0x00FF00, 0x8B4513,
		env->ft.lev + 1, lev));
	new_params[1].x = cos(dg_to_rd(env->ft.tilte - env->ft.close)) * params[1].x
		- sin(dg_to_rd(env->ft.tilte - env->ft.close)) * params[1].y;
	new_params[1].y = sin(dg_to_rd(env->ft.tilte - env->ft.close)) * params[1].x
		+ cos(dg_to_rd(env->ft.tilte - env->ft.close)) * params[1].y;
	tree_recur(env, new_params, len / 1.4, lev - 1);
	new_params[1].x = cos(dg_to_rd(env->ft.tilte + env->ft.close)) * params[1].x
		- sin(dg_to_rd(env->ft.tilte + env->ft.close)) * params[1].y;
	new_params[1].y = sin(dg_to_rd(env->ft.tilte + env->ft.close)) * params[1].x
		+ cos(dg_to_rd(env->ft.tilte + env->ft.close)) * params[1].y;
	tree_recur(env, new_params, len / 1.4, lev - 1);
}

void		fill_tree(t_env *env)
{
	t_2point	params[2];

	params[0].x = WIDTH / 2;
	params[0].y = HEIGHT - 1;
	params[1].x = 0;
	params[1].y = -1;
	tree_recur(env, params, HEIGHT / 4, env->ft.lev);
}
