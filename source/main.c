#include "header.h"

#define XER_SLONA 255

void	draw(t_env *env)
{
	int			x;
	int			y;
	t_complex	z;
	t_complex	z_next;
	int			i;
	t_complex	scale;
	int			*image_data;
	int			bits_per_pixel;
	int			line_size;
	int			endian;

	env->image != NULL ? mlx_destroy_image(env->mlx, env->image) : 0;
	env->image = mlx_new_image(env->mlx, env->width, env->height);
	bits_per_pixel = 32;
	line_size = env->width * 4;
	endian = 0;
	image_data = (int *)mlx_get_data_addr(env->image, &bits_per_pixel, &line_size, &endian);
	y = -1;
	while (++y < env->height)
	{
		x = -1;
		while (++x < env->width)
		{
			i = -1;
			z.re = 0;
			z.im = 0;
			scale.re = env->center.re + (x - env->width / 2) * env->scale;
			scale.im = env->center.im + (y - env->height / 2) * env->scale;
			while ((z.re * z.re + z.im * z.im) < 4 && ++i < 255)
			{
				z_next.re = z.re * z.re - z.im * z.im + scale.re;
				z_next.im = 2 * z.re * z.im + scale.im;
				z.re = z_next.re;
				z.im = z_next.im;
			}
			if (i == 0)
				image_data[y * env->width + x] = WHITE;
			else if (i == 255)
				image_data[y * env->width + x] = BLACK;
			else if (i % 3 == 0)
				image_data[y * env->width + x] = get_color(0, 0, 255);
			else if (i % 3 == 1)
				image_data[y * env->width + x] = get_color(255, 0, 0);
			else if (i % 3 == 2)
				image_data[y * env->width + x] = get_color(0, 255, 0);
		}
	}
	mlx_put_image_to_window (env->mlx, env->wind, env->image, 0, 0);
}

t_env	*get_env()
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->mlx = mlx_init();
	env->width = 1200;
	env->height = 900;
	env->wind = mlx_new_window(env->mlx, env->width, env->height, "Fractol");
	env->scale = 0.005;
	env->center.re = -0.75;
	env->center.im = 0;
	env->image = NULL;
	return (env);
}

int 	main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 2)
	{
		if (ft_strcmp(argv[1], "Mandelbrot") && ft_strcmp(argv[1], "Julia") && ft_strcmp(argv[1], "MyFract"))
			exit(show_usage_error());
		env = get_env();
		draw(env);
		mlx_hook(env->wind, 2, 0, key_handler, env);
		mlx_mouse_hook(env->wind, mouse_handler, env);
		mlx_hook(env->wind, 17, 0, (int (*)())&exit, env);
		mlx_loop(env->mlx);
	}
	else
		exit(show_usage_error());
	return (0);
}
