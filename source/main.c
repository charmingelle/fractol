#include "../includes/header.h"

void	draw(t_env *env)
{
	ft_bzero(env->image_data, WIDTH * HEIGHT * 4);
	ft_bzero(env->z_buff, WIDTH * HEIGHT * 8);
	fill_fract_image(env);
	mlx_put_image_to_window(env->mlx, env->wind, env->image, 0, 0);
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
