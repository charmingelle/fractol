#include "header.h"

t_point			get_modified_point(t_env *env, t_point point)
{
	t_point p0;
	t_point p1;
	t_point rotated;

	p0.x = point.x;
	p0.y = (point.y * cos(degree_to_rad(env->ang_x)) + point.z
		* sin(degree_to_rad(env->ang_x)));
	p0.z = (point.z * cos(degree_to_rad(env->ang_x)) - point.y
		* sin(degree_to_rad(env->ang_x)));
	p1.x = p0.x * cos(degree_to_rad(env->ang_y)) - p0.z
		* sin(degree_to_rad(env->ang_y));
	p1.y = p0.y;
	p1.z = p0.z * cos(degree_to_rad(env->ang_y)) + p0.x
		* sin(degree_to_rad(env->ang_y));
	// rotated.x = (p1.x * cos(degree_to_rad(env->ang_z)) + p1.y
	// 	* sin(degree_to_rad(env->ang_z))) + WIDTH /2;
	// rotated.y = (p1.y * cos(degree_to_rad(env->ang_z)) - p1.x
	// 	* sin(degree_to_rad(env->ang_z))) + HEIGHT / 2;
	// rotated.z = p1.z;
	rotated.x = (p1.x * cos(degree_to_rad(env->ang_z)) + p1.y
		* sin(degree_to_rad(env->ang_z)));
	rotated.y = (p1.y * cos(degree_to_rad(env->ang_z)) - p1.x
		* sin(degree_to_rad(env->ang_z)));
	rotated.z = p1.z;
	return (rotated);
}