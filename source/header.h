#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

# include <stdio.h>

# define ESC 53
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define SCALE_COEFFICIENT 20
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00

typedef struct	s_complex
{
	double	re;
	double	im;
}				t_complex;

typedef struct	s_env
{
	void		*mlx;
	void		*wind;
	int			width;
	int			height;
	double		scale;
	t_complex	center;
	void		*image;
}				t_env;

int			show_usage_error();

double		get_re(t_complex a);

double		get_im(t_complex a);

t_complex	get_sum(t_complex a, t_complex b);

t_complex	get_prod(t_complex a, t_complex b);

double		get_mod(t_complex a);

int			key_handler(int keycode, t_env *env);

int			mouse_handler(int button, int x, int y, t_env *env);

void		draw(t_env *env);

int			get_mid_color(int start, int end, double to_pass, double passed);

int			get_color(int r, int g, int b);

#endif
