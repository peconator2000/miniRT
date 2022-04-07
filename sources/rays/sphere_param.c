#include "miniRT.h"

void	sphere_param(double *min_t, t_color *min_c,	t_figures *sp, t_scene *sc, t_ray ray)
{
	t_point		sp_dot;
	t_point		norm;

	(*min_c) = sp->color;
	get_ray_dot(&sp_dot, ray, *(min_t));
	vec_fill(&norm, sp_dot.x - sp->fig.sp.coord.x, sp_dot.y - sp->fig.sp.coord.y, sp_dot.z - sp->fig.sp.coord.z);
	normalize2(&norm, norm);
	(*min_c) = compute_color(sc, sp, ray.op, sp_dot);
}
