#include "miniRT.h"

void	plane_param(double *min_t, t_color *min_color,	t_figures *pl, t_scene *sc, t_ray ray)
{
	t_point		pl_dot;
	t_point		norm;

	(*min_color) = pl->color;
	get_ray_dot(&pl_dot, ray, *(min_t));
	vec_fill(&norm, pl->no_vec.x, pl->no_vec.y, pl->no_vec.z);
	normalize2(&norm, norm);
	(*min_color) = compute_color(sc, pl, ray.op, pl_dot);
}
