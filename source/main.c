#include "header.h"

void	clear_z_buffer(t_env *env)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH)
			env->z_buff[y * WIDTH + x] = 0;
}

int		get_fract_color(int i)
{
	static int palette[] = {
		0x800000, 0x8B0000, 0xA52A2A, 0xB22222, 0xDC143C, 0xFF0000, 0xFF6347,
		0xFF7F50, 0xCD5C5C, 0xF08080, 0xE9967A, 0xFA8072, 0xFFA07A, 0xFF4500,
		0xFF8C00, 0xFFA500, 0xFFD700, 0xB8860B, 0xDAA520, 0xEEE8AA, 0xBDB76B,
		0xF0E68C, 0x808000, 0xFFFF00, 0x9ACD32, 0x556B2F, 0x6B8E23, 0x7CFC00,
		0x7FFF00, 0xADFF2F, 0x006400, 0x008000, 0x228B22, 0x00FF00, 0x32CD32,
		0x90EE90, 0x98FB98, 0x8FBC8F, 0x00FA9A, 0x00FF7F, 0x2E8B57, 0x66CDAA,
		0x3CB371, 0x20B2AA, 0x2F4F4F, 0x008080, 0x008B8B, 0x00FFFF, 0x00FFFF,
		0xE0FFFF, 0x00CED1, 0x40E0D0, 0x48D1CC, 0xAFEEEE, 0x7FFFD4, 0xB0E0E6,
		0x5F9EA0, 0x4682B4, 0x6495ED, 0x00BFFF, 0x1E90FF, 0xADD8E6, 0x87CEEB,
		0x87CEFA, 0x191970, 0x000080, 0x00008B, 0x0000CD, 0x0000FF, 0x4169E1,
		0x8A2BE2, 0x4B0082, 0x483D8B, 0x6A5ACD, 0x7B68EE, 0x9370DB, 0x8B008B,
		0x9400D3, 0x9932CC, 0xBA55D3, 0x800080, 0xD8BFD8, 0xDDA0DD, 0xEE82EE,
		0xFF00FF, 0xDA70D6, 0xC71585, 0xDB7093, 0xFF1493, 0xFF69B4, 0xFFB6C1,
		0xFFC0CB, 0xFAEBD7, 0xF5F5DC, 0xFFE4C4, 0xFFEBCD, 0xF5DEB3, 0xFFF8DC,
		0xFFFACD, 0xFAFAD2, 0xFFFFE0, 0x8B4513, 0xA0522D, 0xD2691E, 0xCD853F,
		0xF4A460, 0xDEB887, 0xD2B48C, 0xBC8F8F, 0xFFE4B5, 0xFFDEAD, 0xFFDAB9,
		0xFFE4E1, 0xFFF0F5, 0xFAF0E6, 0xFDF5E6, 0xFFEFD5, 0xFFF5EE, 0xF5FFFA,
		0x708090, 0x778899, 0xB0C4DE, 0xE6E6FA, 0xFFFAF0, 0xF0F8FF, 0xF8F8FF,
		0xF0FFF0, 0xFFFFF0, 0xF0FFFF, 0xFFFAFA, 0x000000, 0x696969, 0x808080,
		0xA9A9A9, 0xC0C0C0, 0xD3D3D3, 0xDCDCDC, 0xF5F5F5, 0xFFFFFF
	};

	return (palette[i % 139]);
}

void	fill_tricorn(t_env *env)
{
	int			x;
	int			y;
	t_complex	z;
	double		temp;
	int			i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			i = -1;
			z.re = 0;
			z.im = 0;
			while ((z.re * z.re + z.im * z.im) < 4 && ++i < 256)
			{
				temp = z.re * z.re - z.im * z.im + env->fract.shift.re + (x - WIDTH / 2) * env->fract.scale;
				z.im = -2 * z.re * z.im + env->fract.shift.im + (y - HEIGHT / 2) * env->fract.scale;
				z.re = temp;
			}
			env->image_data[y * WIDTH + x] = get_fract_color(i);
		}
	}
}

void	fill_mandel(t_env *env)
{
	int			x;
	int			y;
	t_complex	z;
	double		temp;
	int			i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			i = -1;
			z.re = 0;
			z.im = 0;
			while ((z.re * z.re + z.im * z.im) < 4 && ++i < 256)
			{
				temp = z.re * z.re - z.im * z.im + env->fract.shift.re + (x - WIDTH / 2) * env->fract.scale;
				z.im = 2 * z.re * z.im + env->fract.shift.im + (y - HEIGHT / 2) * env->fract.scale;
				z.re = temp;
			}
			env->image_data[y * WIDTH + x] = get_fract_color(i);
		}
	}
}

void	fill_ship(t_env *env)
{
	int			x;
	int			y;
	t_complex	z;
	double		temp;
	int			i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			i = -1;
			z.re = 0;
			z.im = 0;
			while ((z.re * z.re + z.im * z.im) < 4 && ++i < 256)
			{
				temp = z.re * z.re - z.im * z.im + env->fract.shift.re + (x - WIDTH / 2) * env->fract.scale;
				z.im = 2 * fabs(z.re * z.im) + env->fract.shift.im + (y - HEIGHT / 2) * env->fract.scale;
				z.re = temp;
			}
			env->image_data[y * WIDTH + x] = get_fract_color(i);
		}
	}
}

void	fill_julia(t_env *env)
{
	int			x;
	int			y;
	t_complex	z;
	double		temp;
	int			i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			i = -1;
			z.re = 1.5 * (x - WIDTH / 2) / (0.5 * env->fract.scale * WIDTH) + env->fract.pivot.re;
			z.im = (y - HEIGHT / 2) / (0.5 * env->fract.scale * HEIGHT) + env->fract.pivot.im;
			while ((z.re * z.re + z.im * z.im) < 4 && ++i < 255)
			{
				temp = z.re * z.re - z.im * z.im + env->fract.shift.re;
				z.im = 2 * z.re * z.im + env->fract.shift.im;
				z.re = temp;
			}
			env->image_data[y * WIDTH + x] = get_fract_color(i);
		}
	}
}

void	draw(t_env *env)
{
	ft_bzero(env->image_data, WIDTH * HEIGHT * 4);
	ft_bzero(env->z_buff, WIDTH * HEIGHT * 8);
	if (env->fract_type == 1)
		fill_mandel(env);
	else if (env->fract_type == 2)
		fill_julia(env);
	else if (env->fract_type == 3)
		fill_bulb(env);
	else if (env->fract_type == 4)
		fill_apoll(env);
	else if (env->fract_type == 5)
		fill_serp(env);
	else if (env->fract_type == 6)
		fill_tricorn(env);
	else if (env->fract_type == 7)
		fill_ship(env);
	else if (env->fract_type == 8)
		fill_cantor(env);
	else if (env->fract_type == 9)
		fill_tree(env);
	mlx_put_image_to_window(env->mlx, env->wind, env->image, 0, 0);
}

t_env	*get_env(void *mlx, int fract)
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
	if (fract == 1)
	{
		env->fract_type = 1;
		env->fract.scale = 0.005;
		env->fract.shift.re = -0.75;
		env->fract.shift.im = 0;
	}
	else if (fract == 2)
	{
		env->fract_type = 2;
		env->fract.scale = 1;
		env->fract.shift.re = -0.7;
		env->fract.shift.im = 0.27015;
		env->fract.pivot.re = 0.0;
		env->fract.pivot.re = 0.1;
	}
	else if (fract == 3)
	{
		env->fract_type = 3;
		env->fract.scale = 0.000005;
		env->fract.shift.re = 0;
		env->fract.shift.im = 0;
	}
	else if (fract == 4)
	{
		env->fract_type = 4;
		env->fract.lev = 0;
	}
	else if (fract == 5)
	{
		env->fract_type = 5;
		env->fract.lev = 0;
		env->fract.len = MIN(WIDTH, HEIGHT) / 1.3;
	}
	else if (fract == 6)
	{
		env->fract_type = 6;
		env->fract.scale = 0.005;
		env->fract.shift.re = -0.75;
		env->fract.shift.im = 0;
	}
	else if (fract == 7)
	{
		env->fract_type = 7;
		env->fract.scale = 0.005;
		env->fract.shift.re = -0.75;
		env->fract.shift.im = 0;
	}
	else if (fract == 8)
	{
		env->fract_type = 8;
		env->fract.lev = 0;
		env->fract.len = MIN(WIDTH, HEIGHT) / 2;
	}
	else if (fract == 9)
	{
		env->fract_type = 9;
		env->fract.lev = 0;
		env->fract.tilte = 0;
		env->fract.closeness = 45;
	}
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
		if (ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 9)
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
