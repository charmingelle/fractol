#include "header.h"

void	draw(t_env *env)
{
	ft_bzero(env->image_data, WIDTH * HEIGHT * 4);
	ft_bzero(env->z_buff, WIDTH * HEIGHT * 8);
	fill_fract_image(env);
	mlx_put_image_to_window(env->mlx, env->wind, env->image, 0, 0);
	mlx_string_put(env->mlx, env->wind, 10, 10, 0xFFFFFF, env->fract.man);
}

static t_cl	get_cl(t_env *env)
{
	t_cl	cl;

	if (!(cl.fd = open(env->fract.file, O_RDONLY)))
		show_kernel_error();
	cl.source_str = (char*)malloc(MAX_SOURCE_SIZE);
	cl.source_size = read(cl.fd, cl.source_str, MAX_SOURCE_SIZE);
	close(cl.fd);
	cl.ret = clGetPlatformIDs(1, &cl.platform_id, &cl.ret_num_platforms);
	cl.ret = clGetDeviceIDs(cl.platform_id, CL_DEVICE_TYPE_GPU, 1, &cl.device_id, &cl.ret_num_devices);
	cl.context = clCreateContext(NULL, 1, &cl.device_id, NULL, NULL, &cl.ret);
	cl.command_queue = clCreateCommandQueue(cl.context, cl.device_id, 0, &cl.ret);
	cl.memobj = clCreateBuffer(cl.context, CL_MEM_READ_WRITE,  MEM_SIZE * sizeof(char), NULL, &cl.ret);
	cl.program = clCreateProgramWithSource(cl.context, 1, (const char **)&cl.source_str, (const size_t *)&cl.source_size, &cl.ret);
	cl.ret = clBuildProgram(cl.program, 1, &cl.device_id, "-I includes", NULL, NULL);
	cl.kernel = clCreateKernel(cl.program, "hello", &cl.ret);
	return (cl);
}

static t_env	*get_env(void *mlx, int number)
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
	env->juls = 0;
	env->cl = get_cl(env);
	return (env);
}

static void	show_fract_wind(void *mlx, char *arg)
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

static void	validate_fract(int argc, char **argv)
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
