#include "miniRT.h"

static void	get_dist_to_obj(t_scene *scene, t_ray ray_fig,
		double *closest_intersection)
{
	double		dist;
	t_figures	*figs;
	// t_ray		ray_fig;
	// t_point lig;

	figs = scene->figs;
	dist = INFINITY;
	// ray_fig.op = ray;
	// ray_fig.o = scene->light->coord;
	while (figs)
	{
		if (figs->type == SPHERE)
		{
			// ray_fig.p = figs->fig.sp.coord;
			dist = is_sphere(ray_fig, figs);
		}
		else if (figs->type == PLANE)
		{
			// ray_fig.p = figs->fig.sp.coord;
			dist = is_plane(ray_fig, figs);
		}
		else if (figs->type == CYLINDER)
		{
			// get_cy_basis_dot(scene->light->coord, &lig, figs, figs->fig.cy.coord);
			// ray_fig.o = lig;
			// ray_fig.p = ;
			dist = is_cylinder(ray_fig.o, ray_fig.p, figs);
			// dist = EPSILON;
		}
		if (dist > EPSILON && dist < *closest_intersection)
			*closest_intersection = dist;
		figs = figs->next;
	}
}

int	check_shadow(t_scene *scene, t_ray ray, t_figures *figure)
{
	// t_ray	ray;
	double	ray_len;
	double	dist;

	// ray = vector_subtract(intersect, scene->light->coord);
	// ray_fill(&ray, scene->light->coord, intersect);
	ray_len = get_module(ray.op, ray.op);
	ray.op = normalize(ray.op);
	dist = INFINITY;
	get_dist_to_obj(scene, ray, &dist);
	if (dist > EPSILON && dist < ray_len - EPSILON && figure->type != -1)
		return (1);
	return (0);
}
