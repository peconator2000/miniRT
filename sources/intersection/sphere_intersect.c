#include "miniRT.h"


double	sphere_intersect(t_point src_coord,t_point ray, t_figures *figure)
{
	t_sphere	sphere;
	t_point		src_to_sp;
	double		b;
	double		c;
	double		discr;
	double		radius;

	radius = sphere.diameter * 0.5;
	sphere = figure->fig.sp;
	src_to_sp = vector_subtract(src_coord, sphere.coord);
	b = get_dot(src_to_sp, ray);
	c = get_dot(src_to_sp, src_to_sp) - radius * radius;
	discr = b * b - c;
	if (discr < 0)
		return (0);
	return (-b - sqrtf(discr));
}
