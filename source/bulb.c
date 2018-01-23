#include "header.h"

void	fill_bulb(t_env *env)
{
	t_point		c;
	t_point		c_flat;
	t_point		z;
	t_point		z_new;
	int			i;
	int			pos;

	c.x = 0.0;
	while (c.x < WIDTH)
	{
		c.y = 0.0;
		while (c.y < HEIGHT)
		{
			c.z = 0.0;
			while (c.z < WIDTH)
			{
				z.x = 0.005;
				z.y = 0.005;
				z.z = 0.005;
				i = -1;
				while ((z.x * z.x + z.y * z.y + z.z * z.z) < 8 && ++i < 256)
				{
					z_new.x = (3 * z.z * z.z - z.x * z.x - z.y * z.y) * z.x * (z.x * z.x - 3 * z.y * z.y) / (z.x * z.x + z.y * z.y) + (c.x - WIDTH / 2) / WIDTH;
					z_new.y = (3 * z.z * z.z - z.x * z.x - z.y * z.y) * z.y * (3 * z.x * z.x - z.y * z.y) / (z.x * z.x + z.y * z.y) + (c.y - HEIGHT / 2) / HEIGHT;
					z_new.z = z.z * (z.z * z.z - 3 * z.x * z.x - 3 * z.y * z.y) + (c.z - WIDTH / 2) / WIDTH;
					z.x = z_new.x;
					z.y = z_new.y;
					z.z = z_new.z;
				}
				c_flat = get_modified_point(env, c);
				pos = (int)c_flat.y * WIDTH + (int)c_flat.x;
				if (pos < (env->line_size * HEIGHT))
				{
					if (env->z_buff[pos] == 0 || env->z_buff[pos] < c_flat.z)
					{
						env->image_data[pos] = get_fract_color(i);
						env->z_buff[pos] = c_flat.z;
					}
				}
				c.z += 1.0;
			}
			c.y += 1.0;
		}
		c.x += 1.0;
	}
	clear_z_buffer(env);
}
