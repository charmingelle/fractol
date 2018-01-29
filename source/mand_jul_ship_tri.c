#include "../includes/header.h"

void	fill_mandel(t_env *env)
{
	int			x;
	int			y;
	t_2point	z;
	double		temp;
	int			i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			i = -1;
			z.x = 0;
			z.y = 0;
			while ((z.x * z.x + z.y * z.y) < 4 && ++i < 256)
			{
				temp = z.x * z.x - z.y * z.y + env->fract.shift.x + (x - WIDTH / 2) * env->fract.scale;
				z.y = 2 * z.x * z.y + env->fract.shift.y + (y - HEIGHT / 2) * env->fract.scale;
				z.x = temp;
			}
			env->image_data[y * WIDTH + x] = get_palette_color(i);
		}
	}
}

void	fill_julia(t_env *env)
{
	int			x;
	int			y;
	t_2point	z;
	double		temp;
	int			i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			i = -1;
			z.x = 1.5 * (x - WIDTH / 2) / (0.5 * env->fract.scale * WIDTH) + env->fract.pivot.x;
			z.y = (y - HEIGHT / 2) / (0.5 * env->fract.scale * HEIGHT) + env->fract.pivot.y;
			while ((z.x * z.x + z.y * z.y) < 4 && ++i < 255)
			{
				temp = z.x * z.x - z.y * z.y + env->fract.shift.x;
				z.y = 2 * z.x * z.y + env->fract.shift.y;
				z.x = temp;
			}
			env->image_data[y * WIDTH + x] = get_palette_color(i);
		}
	}
}

void	fill_ship(t_env *env)
{
	int			x;
	int			y;
	t_2point	z;
	double		temp;
	int			i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			i = -1;
			z.x = 0;
			z.y = 0;
			while ((z.x * z.x + z.y * z.y) < 4 && ++i < 256)
			{
				temp = z.x * z.x - z.y * z.y + env->fract.shift.x + (x - WIDTH / 2) * env->fract.scale;
				z.y = 2 * fabs(z.x * z.y) + env->fract.shift.y + (y - HEIGHT / 2) * env->fract.scale;
				z.x = temp;
			}
			env->image_data[y * WIDTH + x] = get_palette_color(i);
		}
	}
}

void	fill_tricorn(t_env *env)
{
	int			x;
	int			y;
	t_2point	z;
	double		temp;
	int			i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			i = -1;
			z.x = 0;
			z.y = 0;
			while ((z.x * z.x + z.y * z.y) < 4 && ++i < 256)
			{
				temp = z.x * z.x - z.y * z.y + env->fract.shift.x + (x - WIDTH / 2) * env->fract.scale;
				z.y = -2 * z.x * z.y + env->fract.shift.y + (y - HEIGHT / 2) * env->fract.scale;
				z.x = temp;
			}
			env->image_data[y * WIDTH + x] = get_palette_color(i);
		}
	}
}

void	fill_fract_image(t_env *env)
{
	env->fract.number == MANDEL? fill_mandel(env) : 0;
	env->fract.number == JULIA ? fill_julia(env) : 0;
	env->fract.number == SHIP? fill_ship(env) : 0;
	env->fract.number == TRICORN ? fill_tricorn(env) : 0;
	env->fract.number == APOLL? fill_apoll(env) : 0;
	env->fract.number == TREE ? fill_tree(env) : 0;
	env->fract.number == CANTOR ? fill_cantor(env) : 0;
	env->fract.number == SERP ? fill_serp(env) : 0;
}
