/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:57:34 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/01 20:10:57 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		get_palette_color(int i)
{
	int palette[] = {
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

__kernel void	hello(__global int* image_data, int width, int height, double scale, double shift_x, double shift_y, double pivot_x, double pivot_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	double	temp;
	int	 	i = -1;
	double  z_x = 0.0;
	double  z_y = 0.0;

	while ((z_x * z_x + z_y * z_y) < 4 && ++i < 138)
	{
		temp = z_x * z_x - z_y * z_y + shift_x + (x - width / 2) * scale;
		z_y = 2.0 * fabs(z_x * z_y) + shift_y + (y - height / 2) * scale;
		z_x = temp;
	}
	image_data[y * width + x] = get_palette_color(i);
}
