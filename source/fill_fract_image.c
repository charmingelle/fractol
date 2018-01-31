#include "../includes/header.h"

void	set_cl_args(t_cl *cl, t_env *env)
{
	int		width;
	int		height;

	width = WIDTH;
	height = HEIGHT;
	(cl->ret = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&cl->memobj)) ? exit(show_set_param_error()) : 0;
	(cl->ret = clSetKernelArg(cl->kernel, 1, sizeof(int), (void *)&width)) ? exit(show_set_param_error()) : 0;
	(cl->ret = clSetKernelArg(cl->kernel, 2, sizeof(int), (void *)&height)) ? exit(show_set_param_error()) : 0;
	(cl->ret = clSetKernelArg(cl->kernel, 3, sizeof(double), (void *)&env->fract.scale)) ? exit(show_set_param_error()) : 0;
	(cl->ret = clSetKernelArg(cl->kernel, 4, sizeof(double), (void *)&env->fract.shift.x)) ? exit(show_set_param_error()) : 0;
	(cl->ret = clSetKernelArg(cl->kernel, 5, sizeof(double), (void *)&env->fract.shift.y)) ? exit(show_set_param_error()) : 0;
	(cl->ret = clSetKernelArg(cl->kernel, 6, sizeof(double), (void *)&env->fract.pivot.x)) ? exit(show_set_param_error()) : 0;
	(cl->ret = clSetKernelArg(cl->kernel, 7, sizeof(double), (void *)&env->fract.pivot.y)) ? exit(show_set_param_error()) : 0;
}

void	fill_fract_image_with_cl(t_env *env, char *file_pass)
{
	t_cl	cl;

	if (!(cl.fd = open(file_pass, O_RDONLY)))
		show_kernel_error();
	cl.source_str = (char*)malloc(MAX_SOURCE_SIZE);
	cl.source_size = read(cl.fd, cl.source_str, MAX_SOURCE_SIZE);
	close(cl.fd);
	cl.ret = clGetPlatformIDs(1, &cl.platform_id, &cl.ret_num_platforms);
	cl.ret = clGetDeviceIDs(cl.platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &cl.device_id, &cl.ret_num_devices);
	cl.context = clCreateContext(NULL, 1, &cl.device_id, NULL, NULL, &cl.ret);
	cl.command_queue = clCreateCommandQueue(cl.context, cl.device_id, 0, &cl.ret);
	cl.memobj = clCreateBuffer(cl.context, CL_MEM_READ_WRITE,  MEM_SIZE * sizeof(char), NULL, &cl.ret);
	cl.program = clCreateProgramWithSource(cl.context, 1, (const char **)&cl.source_str, (const size_t *)&cl.source_size, &cl.ret);
	cl.ret = clBuildProgram(cl.program, 1, &cl.device_id, "-I includes", NULL, NULL);
	cl.kernel = clCreateKernel(cl.program, "hello", &cl.ret);
	set_cl_args(&cl, env);
	cl.ret = clEnqueueNDRangeKernel(cl.command_queue, cl.kernel, 2, NULL, (size_t[3]){WIDTH, HEIGHT, 0}, NULL, 0, NULL, NULL);
	cl.ret = clEnqueueReadBuffer(cl.command_queue, cl.memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), env->image_data, 0, NULL, NULL);
	free(cl.source_str);
}

void	fill_fract_image(t_env *env)
{
	env->fract.number == MANDEL? fill_fract_image_with_cl(env, "./cl/mandel.cl") : 0;
	env->fract.number == JULIA ? fill_fract_image_with_cl(env, "./cl/julia.cl") : 0;
	env->fract.number == SHIP ? fill_fract_image_with_cl(env, "./cl/ship.cl") : 0;
	env->fract.number == TRICORN ? fill_fract_image_with_cl(env, "./cl/tricorn.cl") : 0;
	env->fract.number == APOLL? fill_apoll(env) : 0;
	env->fract.number == TREE ? fill_tree(env) : 0;
	env->fract.number == CANTOR ? fill_cantor(env) : 0;
	env->fract.number == SERP ? fill_serp(env) : 0;
}
