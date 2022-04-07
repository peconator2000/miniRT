#include "miniRT.h"

void	cylinder_param(double *min_t, t_color *min_color, t_figures *cy, t_scene *sc, t_point dot, t_ray ray)
{
	t_ray		new_ray;
	t_point		cy_dot;
	t_point		norm;

	get_cy_basis_dot(sc->camera->pos, &(new_ray.o), cy, cy->fig.cy.coord);
	get_cy_basis_dot(dot, &(new_ray.p), cy, cy->fig.cy.coord);
	ray_fill(&new_ray, new_ray.o, new_ray.p);
	normalize2(&(new_ray.op), new_ray.op);
	(*min_color) = cy->color;
	get_ray_dot(&cy_dot, new_ray, cy->cy_t);
	vec_fill(&norm, cy_dot.x, cy_dot.y, 0);
	normalize2(&norm, norm);
	back_world_basis(&norm, cy);
	back_world_basis(&cy_dot, cy);
	cy_normal(&norm, cy->fig.cy.coord);
	get_ray_dot(&cy_dot, ray, (*min_t));
	(*min_color) = compute_cy_color(sc, cy, cy_dot, norm);
}
