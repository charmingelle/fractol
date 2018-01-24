#include "header.h"

void	fill_tree(t_env *env)
{
	draw_seg(env, (t_point){WIDTH / 2, HEIGHT, 0}, (t_point){WIDTH / 2, HEIGHT - env->fract.len, 0}, WHITE);
}
