#include "header.h"

static t_cube			get_cube(t_point start, int len)
{
	t_cube	cube;

	cube.front_a = start;
	cube.front_b = GMP(start, len - 1, 0, 0);
	cube.front_c = GMP(start, len - 1, len - 1, 0);
	cube.front_d = GMP(start, 0, len - 1, 0);
	cube.back_a = GMP(start, 0, 0, len - 1);
	cube.back_b = GMP(start, len - 1, 0, len - 1);
	cube.back_c = GMP(start, len - 1, len - 1, len - 1);
	cube.back_d = GMP(start, 0, len - 1, len - 1);
	return (cube);
}

static void				cantor_recur(t_env *env, t_cube cube, int len, int step)
{
	len /= 3;
	if (step < env->ft.lev && len > 1)
	{
		cantor_recur(env, get_cube(cube.front_a, len),
									len, step + 1);
		cantor_recur(env, get_cube(GMP(cube.front_b, -len + 1,
									0, 0), len), len, step + 1);
		cantor_recur(env, get_cube(GMP(cube.front_c, -len + 1,
									-len + 1, 0), len), len, step + 1);
		cantor_recur(env, get_cube(GMP(cube.front_d, 0, -len + 1,
									0), len), len, step + 1);
		cantor_recur(env, get_cube(GMP(cube.back_a, 0, 0,
									-len + 1), len), len, step + 1);
		cantor_recur(env, get_cube(GMP(cube.back_b, -len + 1, 0,
									-len + 1), len), len, step + 1);
		cantor_recur(env, get_cube(GMP(cube.back_c, -len + 1,
									-len + 1, -len + 1), len), len, step + 1);
		cantor_recur(env, get_cube(GMP(cube.back_d, 0, -len + 1,
									-len + 1), len), len, step + 1);
	}
	else
		draw_cube(env, cube);
}

void					fill_cantor(t_env *env)
{
	t_cube	cube;
	t_point	start;

	start.x = -env->ft.len / 2;
	start.y = -env->ft.len / 2;
	start.z = -env->ft.len / 2;
	cube = get_cube(start, env->ft.len);
	cantor_recur(env, cube, env->ft.len, 0);
}
