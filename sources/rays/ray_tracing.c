#include "miniRT.h"

void	sphere_param(double *min_t, t_color *min_c,	t_figures *sp, t_scene *sc, t_ray ray, t_minirt *data)
{
	t_point		sp_dot;
	t_point		norm;
	double		t;

	t = is_sphere(ray, sp);
	if (((*min_t) == -1 || t < *min_t) && t != -1)
	{
		(*min_t) = t;
		(*min_c) = sp->color;
		get_ray_dot(&sp_dot, ray, *(min_t));
		vec_fill(&norm, sp_dot.x - sp->fig.sp.coord.x,  sp_dot.y - sp->fig.sp.coord.y,  sp_dot.z - sp->fig.sp.coord.z);
		normalize2(&norm, norm);
		(*min_c) = get_ligth_sphere(sp, sp_dot, (*min_c), sc->light, data);
	}
}

void	plane_param(double *min_t, t_color *min_color,	t_figures *pl, t_scene *sc, t_ray ray, t_minirt *data)
{
	t_point		pl_dot;
	double		t;

(void)data;
	t = is_plane(ray, pl);
	if (((*min_t) == -1 || t < *min_t) && t > 1)
	{
		(*min_t) = t;
		(*min_color) = pl->color;
		get_ray_dot(&pl_dot, ray, *(min_t));
		(*min_color) = compute_color(sc, pl, ray, *min_t, pl->no_vec, pl_dot);
		// get_ligth_plane(pl, pl_dot, (*min_color), sc->light, data);
	}
}

void	cylinder_param(double *min_t, t_color *min_color, t_figures *cy, t_scene *sc, t_point dot, t_ray ray, t_minirt *data)
{
	t_ray		new_ray;
	t_point		cy_dot;
	t_point		norm;
	// t_ray		normal;
	double		t;
	(void)data;
	t = is_cylinder(sc->camera->pos, dot, cy);
	if (((*min_t) == -1 || t < *min_t) && t > 1)
	{
		get_cy_basis_dot(sc->camera->pos, &(new_ray.o), cy, cy->fig.cy.coord);
		get_cy_basis_dot(dot, &(new_ray.p), cy, cy->fig.cy.coord);
		ray_fill(&new_ray, new_ray.o, new_ray.p);
		(*min_t) = t;
		(*min_color) = cy->color;
		get_ray_dot(&cy_dot, new_ray, *(min_t));
		vec_fill(&norm, cy_dot.x, cy_dot.y, 0);
		normalize2(&norm, norm);
		back_world_basis(&norm, cy);
		normalize2(&norm, norm);
		back_world_basis(&cy_dot, cy);
		(void)ray;
		(*min_color) = compute_color(sc, cy, ray, *min_t, norm, cy_dot);
		// (*min_color) = get_ligth_cylinder(cy, cy_dot, normal, (*min_color), sc->light, data);
	}
}

t_color	get_minimal_color(t_minirt *data, t_point dot)
{
	double		min_t;
	t_color		min_color;
	t_figures	*elems;
	t_ray		ray;

	elems = data->scene->figs;
	min_t = -1;
	fill_color(&min_color, 0, 0, 0);
	while (elems)
	{
		ray_fill(&ray, data->scene->camera->pos, dot);
		if (elems->type == PLANE)
			plane_param(&min_t, &min_color, elems,data->scene, ray, data);
		if (elems->type == SPHERE)
			sphere_param(&min_t, &min_color, elems, data->scene, ray, data);
		if (elems->type == CYLINDER)
		// is_cylinder(data->scene, dot, &min_color, &min_t, elems);
			cylinder_param(&min_t, &min_color, elems, data->scene, dot, ray, data);
		elems = elems->next;
	}
	return (min_color);
}

int	get_color(t_minirt *data, double x_sc, double y_sc)
{
	t_color	color;
	t_point	dot;

	get_inscreen(data->scene, &dot, x_sc, y_sc);
	get_new_coords(data->scene->camera, &dot);
	color = get_minimal_color(data, dot);
	return (color.mix);
}
