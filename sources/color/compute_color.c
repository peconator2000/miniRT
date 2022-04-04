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

void get_cy_coord(t_figures *fig, t_point *dot)
{
	t_point	rig;
	t_point	up;
	t_point	dir;

	rig = fig->r;
	up = fig->u;
	dir = fig->d;
	(*dot).x = rig.x * (*dot).x + rig.y * (*dot).y + rig.z * (*dot).z + fig->fig.cy.coord.x;//(rig.x * cam->pos.x + rig.y * cam->pos.y + rig.z * cam->pos.z);
	(*dot).y = up.x * (*dot).x + up.y * (*dot).y + up.z * (*dot).z  + fig->fig.cy.coord.y;//(up.x * cam->pos.x + up.y * cam->pos.y + up.z * cam->pos.z);
	(*dot).z = dir.x * (*dot).x + dir.y * (*dot).y + dir.z * (*dot).z + fig->fig.cy.coord.z;// dir.x * cam->pos.x + dir.y * cam->pos.y + dir.z * cam->pos.z;
}

t_color	compute_color(t_scene *scene, t_figures *figure,
		t_point ray, double dist, t_point intersect)
{
	// t_point	intersect;
	t_point	normal;
	t_point	direction;
	double	rgb[3];

	ft_memset(rgb, 0, 3 * sizeof(double));
	(void)dist;
	// intersect = vector_add(scene->camera->pos, vector_nmultiply(ray, dist));
	normal = get_normal(figure, intersect, ray);
	direction = normalize(vector_subtract(scene->light->coord, intersect));
	add_coeficient(&rgb, scene->a_light, scene->al_color.mix);
	if (get_dot(normal, direction) > 0
		&& !check_shadow(scene, intersect, figure))
	{
		add_coeficient(&rgb, vcos(normal, direction) * scene->light->bri,
			scene->light->color.mix);
		add_coeficient(&rgb, get_specular(scene, normal, intersect),
			scene->light->color.mix);
	}
	return (build_color(figure->color.mix, rgb));
}

t_color	compute_cy_color(t_scene *scene, t_figures *figure,
		t_point ray, double dist, t_point norm, t_point intersect)
{
	// t_point	intersect;
	t_point	normal;
	t_point	direction;
	double	rgb[3];

	ft_memset(rgb, 0, 3 * sizeof(double));
	get_cy_coord(figure, &intersect);
	(void)ray;
	(void)dist;
	// intersect = vector_add(scene->camera->pos, vector_nmultiply(ray, dist));
	normal = norm;
	get_cy_coord(figure, &normal);
	normal = vector_subtract(normal, figure->fig.cy.coord);
	normalize2(&normal, normal);
	direction = normalize(vector_subtract(scene->light->coord, intersect));
	add_coeficient(&rgb, scene->a_light, scene->al_color.mix);
	if (!figure->in_dot && !check_shadow(scene, intersect, figure))
	{
		add_coeficient(&rgb, vcos(normal, direction) * scene->light->bri,
			scene->light->color.mix);
		add_coeficient(&rgb, get_specular(scene, normal, intersect),
			scene->light->color.mix);
	}
	return (build_color(figure->color.mix, rgb));
}
