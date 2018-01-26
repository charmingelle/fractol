#include "header.h"

void tree_recur(t_env *env, t_point start, t_point dir, double len, int lev)
{
	t_point	end;
	t_point	new_dir;

	if (lev < 0 || len < 1)
		return ;
	end.x = start.x + len * dir.x;
	end.y = start.y + len * dir.y;
	draw_seg(env, start, end, get_mid_color(GREEN, BROWN, env->fract.lev + 1, lev));
	new_dir.x = cos(degree_to_rad(env->fract.tilte - env->fract.closeness)) * dir.x - sin(degree_to_rad(env->fract.tilte - env->fract.closeness)) * dir.y;
	new_dir.y = sin(degree_to_rad(env->fract.tilte - env->fract.closeness)) * dir.x + cos(degree_to_rad(env->fract.tilte - env->fract.closeness)) * dir.y;
	tree_recur(env, end, new_dir, len / 1.4, lev - 1);
	new_dir.x = cos(degree_to_rad(env->fract.tilte + env->fract.closeness)) * dir.x - sin(degree_to_rad(env->fract.tilte + env->fract.closeness)) * dir.y;
	new_dir.y = sin(degree_to_rad(env->fract.tilte + env->fract.closeness)) * dir.x + cos(degree_to_rad(env->fract.tilte + env->fract.closeness)) * dir.y;
	tree_recur(env, end, new_dir, len / 1.4, lev - 1);
}

void	fill_tree(t_env *env)
{
	t_point	start;
	t_point	dir;

	start.x = 0;
	start.y = HEIGHT / 2;
	dir.x = 0;
	dir.y = -1;
	tree_recur(env, start, dir, HEIGHT / 4, env->fract.lev);
}
