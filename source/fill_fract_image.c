#include "header.h"

static void	set_cl_args(t_env *env)
{
	int		width;
	int		height;

	width = WIDTH;
	height = HEIGHT;
	(env->cl.ret = clSetKernelArg(env->cl.kernel, 0, sizeof(cl_mem), (void *)&env->cl.memobj)) ? exit(show_set_param_error("memobj")) : 0;
	(env->cl.ret = clSetKernelArg(env->cl.kernel, 1, sizeof(int), (void *)&width)) ? exit(show_set_param_error("width")) : 0;
	(env->cl.ret = clSetKernelArg(env->cl.kernel, 2, sizeof(int), (void *)&height)) ? exit(show_set_param_error("height")) : 0;
	(env->cl.ret = clSetKernelArg(env->cl.kernel, 3, sizeof(double), (void *)&env->fract.scale)) ? exit(show_set_param_error("scale")) : 0;
	(env->cl.ret = clSetKernelArg(env->cl.kernel, 4, sizeof(double), (void *)&env->fract.shift.x)) ? exit(show_set_param_error("shift_x")) : 0;
	(env->cl.ret = clSetKernelArg(env->cl.kernel, 5, sizeof(double), (void *)&env->fract.shift.y)) ? exit(show_set_param_error("shift_y")) : 0;
	(env->cl.ret = clSetKernelArg(env->cl.kernel, 6, sizeof(double), (void *)&env->fract.pivot.x)) ? exit(show_set_param_error("pivot_x")) : 0;
	(env->cl.ret = clSetKernelArg(env->cl.kernel, 7, sizeof(double), (void *)&env->fract.pivot.y)) ? exit(show_set_param_error("pivot_y")) : 0;
}

static void	fill_fract_image_with_cl(t_env *env)
{
	set_cl_args(env);
	env->cl.ret = clEnqueueNDRangeKernel(env->cl.command_queue, env->cl.kernel, 2, NULL, (size_t[3]){WIDTH, HEIGHT, 0}, NULL, 0, NULL, NULL);
	env->cl.ret = clEnqueueReadBuffer(env->cl.command_queue, env->cl.memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), env->image_data, 0, NULL, NULL);
}

void	fill_fract_image(t_env *env)
{
	env->fract.number == MANDEL? fill_fract_image_with_cl(env) : 0;
	env->fract.number == JULIA ? fill_fract_image_with_cl(env) : 0;
	env->fract.number == SHIP ? fill_fract_image_with_cl(env) : 0;
	env->fract.number == TRICORN ? fill_fract_image_with_cl(env) : 0;
	env->fract.number == APOLL? fill_apoll(env) : 0;
	env->fract.number == TREE ? fill_tree(env) : 0;
	env->fract.number == CANTOR ? fill_cantor(env) : 0;
	env->fract.number == SERP ? fill_serp(env) : 0;
}
