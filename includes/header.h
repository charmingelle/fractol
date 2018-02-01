#ifndef HEADER_H
# define HEADER_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <OpenCL/opencl.h>

# define ROUND(x)((long)(x + 0.5))
# define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
# define GMP(p, a, b, c)((t_point){p.x + a, p.y + b, p.z + c})
# define MAX_SOURCE_SIZE 0x100000
# define WIDTH 2560
# define HEIGHT 1440
# define MEM_SIZE WIDTH * HEIGHT * 4
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
# define J 38
# define PLUS 69
# define MINUS 78
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define SCALE_COEFFICIENT 20
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

typedef struct	s_ft
{
	int			number;
	double		scale;
	t_2point	shift;
	t_2point	pivot;
	int			lev;
	int			len;
	int			tilte;
	int			close;
	char		*man;
	char		*file;
}				t_ft;

typedef struct	s_cl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				memobj;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	int					fd;
	char 				*fileName;
	char 				*source_str;
	size_t 				source_size;
}				t_cl;

typedef struct	s_env
{
	void		*mlx;
	int			*wind_amount;
	void		*wind;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
	t_ft		ft;
	void		*image;
	int			*image_data;
	int			ang_x;
	int			ang_y;
	int			ang_z;
	double		z_buff[WIDTH * HEIGHT];
	int			juls_dance;
	t_cl		cl;
}				t_env;

int			show_usage_error(void);

int			show_kernel_error(void);

int			show_set_param_error(char *param);

int			key_handler(int keycode, t_env *env);

int			mouse_handler(int button, int x, int y, t_env *env);

int			mouse_move_handler(int x, int y, t_env *env);

int			close_wind_handler(t_env *env);

int			get_mid_color(int start, int end, double to_pass, double passed);

t_point		get_modified_point(t_env *env, t_point point);

double		dg_to_rd(double degree);

void		clear_z_buffer(t_env *env);

int			get_geom_palette_color(int i);

double		get_2dist(t_2point a, t_2point b);

double		get_dist(t_point a, t_point b);

void		draw_2seg(t_env *env, t_2point start, t_2point end, int lev);

void		draw_triang(t_env *env, t_point p[3], int color);

void		draw_parallelogram(t_env *env, t_point a[2], t_point b[2], int color);

void		draw_cube(t_env *env, t_cube cube);

void		draw_circle(t_env *env, t_circle circle, int color);

void		draw(t_env *env);

void		fill_apoll(t_env *env);

void		fill_tree(t_env *env);

void		fill_cantor(t_env *env);

void		fill_serp(t_env *env);

t_ft		get_ft_data(int number);

void		fill_ft_image(t_env *env);

double		ft_lerp(double a, double b, double t);

#endif
