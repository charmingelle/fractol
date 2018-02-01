/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:56:41 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 20:30:45 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_cl		get_cl(t_env *env)
{
	t_cl	cl;

	if (!(cl.fd = open(env->ft.file, O_RDONLY)))
		show_kernel_error();
	cl.source_str = (char*)malloc(MAX_SOURCE_SIZE);
	cl.source_size = read(cl.fd, cl.source_str, MAX_SOURCE_SIZE);
	close(cl.fd);
	cl.ret = clGetPlatformIDs(1, &cl.platform_id, &cl.ret_num_platforms);
	cl.ret = clGetDeviceIDs(cl.platform_id, CL_DEVICE_TYPE_CPU, 1,
		&cl.device_id, &cl.ret_num_devices);
	cl.context = clCreateContext(NULL, 1, &cl.device_id, NULL, NULL, &cl.ret);
	cl.command_queue = clCreateCommandQueue(cl.context, cl.device_id,
		0, &cl.ret);
	cl.memobj = clCreateBuffer(cl.context, CL_MEM_READ_WRITE,
		WIDTH * HEIGHT * 4 * sizeof(char), NULL, &cl.ret);
	cl.program = clCreateProgramWithSource(cl.context, 1,
		(const char**)&cl.source_str, (const size_t*)&cl.source_size, &cl.ret);
	cl.ret = clBuildProgram(cl.program, 1, &cl.device_id, NULL, NULL, NULL);
	cl.kernel = clCreateKernel(cl.program, "hello", &cl.ret);
	return (cl);
}

static t_env	*get_env(void *mlx, int *wind_amount, int number)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->mlx = mlx;
	env->wind_amount = wind_amount;
	env->bits_per_pixel = 32;
	env->line_size = WIDTH * 4;
	env->endian = 0;
	env->wind = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Fractol");
	env->image = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->image_data = (int *)mlx_get_data_addr(env->image,
		&env->bits_per_pixel, &env->line_size, &env->endian);
	env->ft = get_ft_data(number);
	env->ang_x = 205;
	env->ang_y = 10;
	env->ang_z = 0;
	env->juls_dance = 0;
	env->cl = get_cl(env);
	return (env);
}

static void		show_ft_wind(void *mlx, int *wind_amount, char *arg)
{
	t_env	*env;

	env = get_env(mlx, wind_amount, ft_atoi(arg));
	draw(env);
	mlx_mouse_hook(env->wind, mouse_handler, env);
	mlx_hook(env->wind, KEY_DOWN, 0, key_handler, env);
	mlx_hook(env->wind, CROSS_CLICK, 0, close_wind_handler, env);
	mlx_hook(env->wind, MOUSE_MOVE, 0, mouse_move_handler, env);
}

int				main(int argc, char **argv)
{
	void	*mlx;
	int		wind_amount;
	int		i;

	if (argc > 1)
	{
		validate_ft(argc, argv);
		mlx = mlx_init();
		wind_amount = argc - 1;
		i = 0;
		while (++i < argc)
			show_ft_wind(mlx, &wind_amount, argv[i]);
		mlx_loop(mlx);
	}
	else
		exit(show_usage_error());
	return (0);
}
