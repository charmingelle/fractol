#include "../includes/header.h"

double	degree_to_rad(int degree)
{
	return (((double)degree * M_PI) / 180.0);
}

double	get_2dist(t_2point a, t_2point b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

double	get_dist(t_point a, t_point b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)));
}

void	clear_z_buffer(t_env *env)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH)
			env->z_buff[y * WIDTH + x] = 0;
}

int		get_geom_palette_color(int i)
{
	static int palette[] = {
		0xFF0000,
		0xFF7F00,
		0xFFFF00,
		0x00FF00,
		0x38EEFF,
		0x0000FF,
		0x9400D3
	};

	return (palette[i % 7]);
}

double	ft_lerp(double a, double b, double t)
{
	return ((1.0 - t) * a + b * t);
}
