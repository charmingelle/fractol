#include "../includes/header.h"

inline static t_point	get_moved_point(t_point point, double x_shift,
										double y_shift, double z_shift)
{
	return ((t_point){point.x + x_shift, point.y + y_shift, point.z + z_shift});
}

static t_cube			get_cube(t_point start, int len)
{
	t_cube	cube;

	cube.front_a = start;
	cube.front_b = get_moved_point(start, len - 1, 0, 0);
	cube.front_c = get_moved_point(start, len - 1, len - 1, 0);
	cube.front_d = get_moved_point(start, 0, len - 1, 0);
	cube.back_a = get_moved_point(start, 0, 0, len - 1);
	cube.back_b = get_moved_point(start, len - 1, 0, len - 1);
	cube.back_c = get_moved_point(start, len - 1, len - 1, len - 1);
	cube.back_d = get_moved_point(start, 0, len - 1, len - 1);
	return (cube);
}

static void				cantor_recur(t_env *env, t_cube cube, int len, int step)
{
	len /= 3;
	if (step < env->fract.lev && len > 1)
	{
		cantor_recur(env, get_cube(cube.front_a, len),
									len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.front_b, -len + 1,
									0, 0), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.front_c, -len + 1,
									-len + 1, 0), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.front_d, 0, -len + 1,
									0), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.back_a, 0, 0,
									-len + 1), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.back_b, -len + 1, 0,
									-len + 1), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.back_c, -len + 1,
									-len + 1, -len + 1), len), len, step + 1);
		cantor_recur(env, get_cube(get_moved_point(cube.back_d, 0, -len + 1,
									-len + 1), len), len, step + 1);
	}
	else
		draw_cube(env, cube);
}

void					fill_cantor(t_env *env)
{
	t_cube	cube;
	t_point	start;

	start.x = -env->fract.len / 2;
	start.y = -env->fract.len / 2;
	start.z = -env->fract.len / 2;
	cube = get_cube(start, env->fract.len);
	cantor_recur(env, cube, env->fract.len, 0);
}
