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
