#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

# include <stdio.h>

# define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
# define WIDTH 1200
# define HEIGHT 1000
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
# define BROWN 0x8B4513

# define MANDEL 1
# define JULIA 2
# define SHIP 3
# define TRICORN 4
# define APOLL 5
# define TREE 6
# define CANTOR 7
# define SERP 8

typedef struct	s_2point
{
	double	x;
	double	y;
}				t_2point;

typedef struct	s_circle
{
	t_2point	center;
	double		rad;
}				t_circle;

typedef struct	s_triag
{
	t_2point	a;
	t_2point	b;
	t_2point	c;
}				t_triag;

typedef struct	s_point
{
	double	x;
	double	y;
	double	z;
}				t_point;

typedef struct	s_pyr
{
	t_point		top;
	t_point		a;
	t_point		b;
	t_point		c;
}				t_pyr;

typedef struct	s_cude
{
	t_point	front_a;
	t_point	front_b;
	t_point	front_c;
	t_point	front_d;
	t_point	back_a;
	t_point	back_b;
	t_point	back_c;
	t_point	back_d;
}				t_cube;

typedef struct	s_complex
{
	double	re;
	double	im;
}				t_complex;

typedef struct	s_fract
{
	double		scale;
	t_complex	shift;
	t_complex	pivot;
	int			lev;
	int			len;
	int			tilte;
	int			closeness;
}				t_fract;

typedef struct	s_env
{
	void		*mlx;
	void		*wind;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
	int			fract_type;
	t_fract		fract;
	void		*image;
	int			*image_data;
	int			ang_x;
	int			ang_y;
	int			ang_z;
	double		z_buff[WIDTH * HEIGHT];
}				t_env;

typedef struct	s_main_wind_env
{
	void	*mlx;
	void	*wind;
}				t_main_wind_env;

int			show_usage_error();

int			key_handler(int keycode, t_env *env);

int			mouse_handler(int button, int x, int y, t_env *env);

int			mouse_move_handler(int x, int y, t_env *env);

void		draw(t_env *env);

int			get_mid_color(int start, int end, double to_pass, double passed);

int			get_color(int r, int g, int b);

t_point		get_modified_point(t_env *env, t_point point);

void		draw_circle(t_env *env, t_circle circle, int lev);

double		degree_to_rad(int degree);

void		fill_apoll(t_env *env);

void		clear_z_buffer(t_env *env);

int			get_fract_color(int i);

void		fill_serp(t_env *env);

double		get_2dist(t_2point a, t_2point b);

double		get_dist(t_point a, t_point b);

void		fill_cantor(t_env *env);

void		fill_tree(t_env *env);

void		draw_seg(t_env *env, t_point a, t_point b, int color);

void		draw_2seg(t_env *env, t_2point start, t_2point end, int lev);

void		draw_parallelogram(t_env *env, t_point a[2], t_point b[2], int color);

void		draw_cube(t_env *env, t_cube cube);

void		sort(t_point *array);

void		draw_triang(t_env *env, t_point p[3], int color);

#endif
