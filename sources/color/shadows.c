#include "miniRT.h"

// static void	get_dist_to_obj(t_scene *scene, t_point ray,
// 		double *closest_intersection)
// {
// 	double		dist;
// 	t_figures	*figs;
// 	t_ray		ray_fig;

// 	figs = scene->figs;
// 	dist = INFINITY;
// 	(void)ray;
// 	// ray_fig.op = ray;
// 	// ray_fig.o = scene->light->coord;
// 	while (figs)
// 	{
// 		if (figs->type == SPHERE)
// 		{
// 			// ray_fig.p = figs->fig.sp.coord;
// 			dist = is_sphere(ray_fig, figs);
// 		}
// 		else if (figs->type == PLANE)
// 		{
// 			// ray_fig.p = figs->fig.sp.coord;
// 			dist = is_plane(ray_fig, figs);
// 		}
// 		else if (figs->type == CYLINDER)
// 		{
// 			// ray_fig.p = figs->fig.cy.coord;
// 			// dist = is_cylinder(ray_fig.o, ray_fig.p, figs);
// 			// printf("dist = %f\n", dist);
// 			// get_cy_basis_dot(scene->light->coord, &(ray_fig.o), figs, figs->fig.cy.coord);
// 			// get_cy_basis_dot(figs->fig.cy.coord, &(ray_fig.p), figs, figs->fig.cy.coord);


// 		}
// 		if (dist > EPSILON && dist < *closest_intersection)
// 			*closest_intersection = dist;
// 		figs = figs->next;
// 	}
// }

void show_type(t_figures *fig, char *str)
{
	if (fig->type == SPHERE)
		printf("shpere %s\n", str);
	else if (fig->type == PLANE)
		printf("plane %s\n", str);
	else if (fig->type == CYLINDER)
		printf("cylinder %s\n", str);
}

static void	get_dist_to_obj(t_scene *scene, t_ray ray_fig,
		double *closest_intersection)
{
	double		dist;
	t_figures	*figs;
	// static int first;
	// static int second;
	// static int third;
	// t_ray		ray_cy;

	figs = scene->figs;
	dist = -1;
	while (figs)
	{
		if (figs->type == SPHERE && !(figs->is_check))
		{
			*closest_intersection = is_sphere(ray_fig, figs, 0.00001);
		}
		else if (figs->type == PLANE && !(figs->is_check))
		{
			*closest_intersection = is_plane(ray_fig, figs);
		}
		else if (figs->type == CYLINDER && !(figs->is_check))
		{
			*closest_intersection = is_cylinder(ray_fig.o, ray_fig.p, figs, 0.00001);
		}
		if (*closest_intersection > 0.00001)
			return ;
		// if (*closest_intersection == -1 || (dist > 0.0001 && dist < *closest_intersection))
		// 	*closest_intersection = dist;
		figs = figs->next;
	}
}

int	check_shadow(t_scene *scene, t_point intersect, t_figures *figure)
{
	t_ray	ray;
	double	ray_len;
	double	dist;

	ray_fill(&ray, intersect, scene->light->coord);
	// normalize2(&ray.op, ray.op);
	ray_len = get_module(ray.op, ray.op);
	ray.op = normalize(ray.op);
	dist = -1;
	// show_type(figure, "dot on figure");
	figure->is_check = 1;
	get_dist_to_obj(scene, ray, &dist);
	figure->is_check = 0;
	if (dist == -1)
		return (0);
		(void)figure;
	if (dist > EPSILON && dist < ray_len - EPSILON && figure->type != -1)
		return (1);
	return (0);
}
