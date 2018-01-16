#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

# include <stdio.h>

# define KEY_DOWN 2
# define CROSS_CLICK 17
# define MOUSE_MOVE 6
# define ESC 53
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14
# define SCALE_COEFFICIENT 20
# define BLACK 0x000000
# define RED 0xFF0000
# define ORANGE 0xFF7F00
# define YELLOW 0xFFFF00
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define INDIGO 0x4B0082
# define VIOLET 0x9400D3
# define WHITE 0xFFFFFF

typedef struct	s_point
{
	double	x;
	double	y;
	double	z;
}				t_point;

typedef struct	s_complex
{
	double	re;
	double	im;
}				t_complex;

typedef struct	s_fract
{
	double		scale;
	t_complex	shift;
}				t_fract;

typedef struct	s_env
{
	void		*mlx;
	void		*wind;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
	int			fract_type;
	t_fract		fract;
	void		*image;
	int			palette[7];
	int			ang_x;
	int			ang_y;
	int			ang_z;
}				t_env;

int			show_usage_error();

double		get_re(t_complex a);

double		get_im(t_complex a);

t_complex	get_sum(t_complex a, t_complex b);

t_complex	get_prod(t_complex a, t_complex b);

double		get_mod(t_complex a);

int			key_handler(int keycode, t_env *env);

int			mouse_handler(int button, int x, int y, t_env *env);

int			mouse_move_handler(int x, int y, t_env *env);

void		draw(t_env *env);

int			get_mid_color(int start, int end, double to_pass, double passed);

int			get_color(int r, int g, int b);

t_point			get_modified_point(t_env *env, t_point point);

#endif
