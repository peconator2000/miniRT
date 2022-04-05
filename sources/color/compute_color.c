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

t_color	compute_color(t_scene *scene, t_figures *figure,
		t_ray ray, double dist, t_point normal, t_point dot)
{
	t_ray	direction;
	double	rgb[3];

	ft_memset(rgb, 0, 3 * sizeof(double));
	(void)ray;
	(void)dist;
	ray_fill(&direction, dot, scene->light->coord);
	add_coeficient(&rgb, scene->a_light, scene->al_color.mix);
	if (get_dot(normal, direction.op) > 0 && !figure->in_dot && !check_shadow(scene, direction, figure))
	{
		add_coeficient(&rgb, vcos(normal, direction.op) * scene->light->bri,
			scene->light->color.mix);
		add_coeficient(&rgb, get_specular(scene, normal, dot),
			scene->light->color.mix);
	}
	return (build_color(figure->color.mix, rgb));
}

t_color	compute_cy_color(t_scene *scene, t_figures *figure,
		t_ray ray, double dist, t_point norm, t_point intersect)
{
	// t_point	intersect;
	t_point	normal;
	t_point	direction;
	double	rgb[3];
	t_point new_lig;

	ft_memset(rgb, 0, 3 * sizeof(double));
	normal = norm;
	(void)ray;
	(void)dist;
	get_cy_basis_dot(scene->light->coord, &new_lig, figure, figure->fig.cy.coord);
	direction = normalize(vector_subtract(new_lig, intersect));
	add_coeficient(&rgb, scene->a_light, scene->al_color.mix);
	if (!figure->in_dot)//&& !check_shadow(scene, intersect, figure))
	{
		add_coeficient(&rgb, vcos(normal, direction) * scene->light->bri,
			scene->light->color.mix);
		add_coeficient(&rgb, get_specular(scene, normal, intersect),
			scene->light->color.mix);
	}
	return (build_color(figure->color.mix, rgb));
}
