#include "miniRT.h"

double	plane_intersect(t_point src_coord, t_point ray, t_figures *figs)
{
	t_plane	plane;
	double	t;

	plane = figs->fig.pl;
	t = -(get_dot(vector_subtract(src_coord, plane.coord), figs->no_vec)) \
			/ get_dot(ray, figs->no_vec);
	return (t);
}

double	p_intersect(t_point src_coord, t_point ray, t_figures *plane)
{
	t_point o = src_coord;
	// t_point p = plane->fig.pl.coord;
	t_point op = ray;
	double t;
	t_point pl_dot;
	t_point n = plane->no_vec;
	t_point k = plane->fig.pl.coord;
	double	num;
	double	den;
	double	d;

	d = n.x * k.x + n.y * k.y + n.z * k.z;
	num = d - (n.x * o.x + n.y * o.y + n.z * o.z);
	den = n.x * op.x + n.y * op.y + n.z * op.z;
	if (den == 0)
		return (0.000000);
	t = num * pow(den, -1);
	pl_dot.x = op.x * t + o.x;
	pl_dot.y = op.y * t + o.y;
	pl_dot.z = op.z * t + o.z;
	return (t);
}
