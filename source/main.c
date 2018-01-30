#include "../includes/header.h"

void	fill_fract_image_with_cl(t_env *env)
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				memobj;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	int					fd;
	char 				*source_str;
	size_t				source_size;
	int					width;
	int					height;

	printf("%s\n", env->fract.file_name);
	if (!(fd = open(env->fract.file_name, O_RDONLY)))
		show_kernel_error();
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = read(fd, source_str, MAX_SOURCE_SIZE);
	close(fd);
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE,  MEM_SIZE * sizeof(char), NULL, &ret);
	program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	if (ret == CL_BUILD_PROGRAM_FAILURE)
	{
		size_t log_size;
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		char *log = (char *) malloc(log_size);
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		printf("%s\n", log);
	}
	kernel = clCreateKernel(program, "hello", &ret);
	width = WIDTH;
	height = HEIGHT;
	(ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 1, sizeof(int), (void *)&width)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 2, sizeof(int), (void *)&height)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 3, sizeof(double), (void *)&env->fract.scale)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 4, sizeof(double), (void *)&env->fract.shift.x)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 5, sizeof(double), (void *)&env->fract.shift.y)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 6, sizeof(double), (void *)&env->fract.pivot.x)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 7, sizeof(double), (void *)&env->fract.pivot.y)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 8, sizeof(int), (void *)&env->fract.lev)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 9, sizeof(int), (void *)&env->fract.len)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 10, sizeof(int), (void *)&env->fract.tilte)) ? exit(show_set_param_error()) : 0;
	(ret = clSetKernelArg(kernel, 11, sizeof(int), (void *)&env->fract.closeness)) ? exit(show_set_param_error()) : 0;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, (size_t[3]){WIDTH, HEIGHT, 0}, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), env->image_data, 0, NULL, NULL);
	free(source_str);
}

void	draw(t_env *env)
{
	ft_bzero(env->image_data, WIDTH * HEIGHT * 4);
	ft_bzero(env->z_buff, WIDTH * HEIGHT * 8);
	fill_fract_image_with_cl(env);
	// fill_fract_image(env);
	mlx_put_image_to_window(env->mlx, env->wind, env->image, 0, 0);
	mlx_string_put(env->mlx, env->wind, 10, 10, 0xFFFFFF, env->fract.man);
}

t_env	*get_env(void *mlx, int number)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->mlx = mlx;
	env->bits_per_pixel = 32;
	env->line_size = WIDTH * 4;
	env->endian = 0;
	env->wind = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Fractol");
	env->image = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->image_data = (int *)mlx_get_data_addr(env->image, &env->bits_per_pixel, &env->line_size, &env->endian);
	env->fract = get_fract_data(number);
	env->ang_x = 0;
	env->ang_y = 0;
	env->ang_z = 0;
	return (env);
}

void	show_fract_wind(void *mlx, char *arg)
{
	t_env	*env;

	env = get_env(mlx, ft_atoi(arg));
	draw(env);
	mlx_mouse_hook(env->wind, mouse_handler, env);
	mlx_hook(env->wind, KEY_DOWN, 0, key_handler, env);
	mlx_hook(env->wind, CROSS_CLICK, 0, (int (*)())&exit, env);
	mlx_hook(env->wind, CROSS_CLICK, 0, mlx_destroy_window, env);
	mlx_hook(env->wind, MOUSE_MOVE, 0, mouse_move_handler, env);
}

void	validate_fract(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 8)
			exit(show_usage_error());
}

int 	main(int argc, char **argv)
{
	void	*mlx;
	int		i;

	if (argc > 1)
	{
		validate_fract(argc, argv);
		mlx = mlx_init();
		i = 0;
		while (++i < argc)
			show_fract_wind(mlx, argv[i]);
		mlx_loop(mlx);
	}
	else
		exit(show_usage_error());
	return (0);
}
