#include "miniRT.h"

static double	get_specular(t_scene *scene, t_point normal, t_point intersect)
{
	double	light;
	t_point	direction;
	t_point	reflected;

	direction = (vector_subtract(scene->light->coord, intersect));
	reflected = (reflect_ray(direction, normal));
	light = scene->light->bri * pow(fmaxf(0.0, vcos(reflected, direction)), 32);
	return (light);
}

static t_point	get_normal(t_figures *figure, t_point intersect)
{
	t_point	normal;

	normal = point_define(0, 0, 0);
	if (figure->type == SPHERE)
		normal = normalize(vector_subtract(intersect, figure->fig.sp.coord));
	else if (figure->type == PLANE)
		normal = normalize(figure->no_vec);
	return (normal);
}

static void	get_dist_to_obj(t_scene *scene, t_point ray, double *closest_intersection)
{
	double		dist;
	t_figures	*figs;

	figs = scene->figs;
	dist = INFINITY;
	while (figs)
	{
		if (figs->type == SPHERE)
			dist = s_intersect(scene->light->coord, ray, figs);
		else if (figs->type == PLANE)
			dist = p_intersect(scene->light->coord, ray, figs);
		if (dist > EPSILON && dist < *closest_intersection)
			*closest_intersection = dist;
		figs = figs->next;
	}
}

static int	check_shadow(t_scene *scene, t_point intersect, t_figures *figure)
{
	t_point	ray;
	double	ray_len;
	double	dist;

	ray = vector_subtract(intersect, scene->light->coord);
	ray_len = get_module(ray, ray);
	ray = normalize(ray);
	dist = INFINITY;
	get_dist_to_obj(scene, ray, &dist);
	if (dist > EPSILON && dist < ray_len - EPSILON && figure->type != -1)
		return (1);
	return (0);
}

t_color	compute_color(t_scene *scene, t_figures *figure, t_point ray, double dist)
{
	t_point	intersect;
	t_point	normal;
	t_point direction;
	double	rgb[3];
	double	light;

	light = 0.0;
	ft_memset(rgb, 0, 3 * sizeof(double));
	intersect = vector_add(scene->camera->pos, vector_nmultiply(ray, dist));
	normal = get_normal(figure, intersect);
	direction = normalize(vector_subtract(scene->light->coord, intersect));
	add_coeficient(&rgb, scene->a_light, scene->al_color.mix);
	if (get_dot(normal, direction) > 0
		&& !check_shadow(scene, intersect, figure))
	{
		light = vcos(normal, direction) * scene->light->bri;
		add_coeficient(&rgb, light, scene->light->color.mix);
		light = get_specular(scene, normal, intersect);
		add_coeficient(&rgb, light, scene->light->color.mix);
	}
	return (build_color(figure->color.mix, rgb));
}
