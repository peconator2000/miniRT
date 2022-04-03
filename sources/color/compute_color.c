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
	if (get_dot(normal, direction) > 0)
	{
		light = vcos(normal, direction) * scene->light->bri;
		add_coeficient(&rgb, light, scene->light->color.mix);
		light = get_specular(scene, normal, intersect);
		add_coeficient(&rgb, light, scene->light->color.mix);
	}
	return (build_color(figure->color.mix, rgb));
}
