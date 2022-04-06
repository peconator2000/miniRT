#include "miniRT.h"

// static double	get_specular(t_scene *scene, t_point normal, t_point intersect)
// {
// 	double	light;
// 	t_point	direction;
// 	t_point	reflected;

// 	direction = (vector_subtract(scene->light->coord, intersect));
// 	reflected = (reflect_ray(direction, normal));
// 	light = scene->light->bri * pow(fmaxf(0.0, vcos(reflected, direction)), 32);
// 	return (light);
// }

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

// t_color	compute_color(t_scene *scene, t_figures *figure,
// 		t_point ray, double dist, t_point intersect)
// {
// 	// t_point	intersect;
// 	t_point	normal;
// 	t_point	direction;
// 	double	rgb[3];
// 	// t_point new_lig;

// 	ft_memset(rgb, 0, 3 * sizeof(double));
// 	(void)dist;
// 	// intersect = vector_add(scene->camera->pos, vector_nmultiply(ray, dist));
// 	normal = get_normal(figure, intersect, ray);
// 	direction = normalize(vector_subtract(scene->light->coord, intersect));
// 	add_coeficient(&rgb, scene->a_light, scene->al_color.mix);
// 	if (!figure->in_dot && !check_shadow(scene, intersect, figure))
// 	{
// 		add_coeficient(&rgb, vcos(normal, direction) * scene->light->bri,
// 			scene->light->color.mix);
// 		add_coeficient(&rgb, get_specular(scene, normal, intersect),
// 			scene->light->color.mix);
// 	}
// 	return (build_color(figure->color.mix, rgb));
// }


t_color	compute_cy_color(t_scene *scene, t_figures *figure,
		t_point ray, double dist, t_point intersect, t_point normal)
{
	t_point	direction;
	double	rgb[3];
	t_color new_color;
	t_color	true_color = figure->color;
	double how;
	t_light light;
	// t_point new_lig;

	ft_memset(rgb, 0, 3 * sizeof(double));
	(void)dist;
	(void)ray;
	light = *(scene->light);
	direction = normalize(vector_subtract(scene->light->coord, intersect));
	// vec_fill(&(direction), scene->light->coord.x - intersect.x, scene->light->coord.y - intersect.y, scene->light->coord.z - intersect.z);
	normalize2(&direction, direction);
	if (figure->in_dot)
	{
		vec_mult_num(&normal, -1);
	}
		how = vec_scalar_mult(normal, direction);
		// printf("how = %f\n", how);
		if (how < 0 || check_shadow(scene, intersect, figure))// || is_shad(data, elem, v1))
		{
			new_color.r = true_color.r * (0.2);
			new_color.g = true_color.g * (0.2);
			new_color.b = true_color.b * (0.2);
			new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
			return (new_color);
		}
		// printf("new tsvet\n");
		new_color.r = true_color.r * (0.2) + true_color.r  * (how *  light.bri);
		new_color.g = true_color.g * (0.2) + true_color.g  * (how * light.bri);
		new_color.b = true_color.b * (0.2) + true_color.b * (how * light.bri);
		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
	// }
	return (new_color);
}

t_color	compute_color(t_scene *scene, t_figures *figure,
		t_point ray, double dist, t_point intersect)
{
	t_point	normal;
	t_point	direction;
	double	rgb[3];
	t_color new_color;
	t_color	true_color = figure->color;
	double how;
	t_light light;

	ft_memset(rgb, 0, 3 * sizeof(double));
	(void)dist;
	light = *(scene->light);
	normal = get_normal(figure, intersect, ray);
	direction = normalize(vector_subtract(scene->light->coord, intersect));
	how = vec_scalar_mult(normal, direction);
	if (how < 0 || check_shadow(scene, intersect, figure))// || is_shad(data, elem, v1))
	{
		new_color.r = true_color.r * (0.2);
		new_color.g = true_color.g * (0.2);
		new_color.b = true_color.b * (0.2);
		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
		return (new_color);
	}
	new_color.r = true_color.r * (0.2) + true_color.r  * (how *  light.bri);
	new_color.g = true_color.g * (0.2) + true_color.g  * (how * light.bri);
	new_color.b = true_color.b * (0.2) + true_color.b * (how * light.bri);
	new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
	return (new_color);
}









// t_color	compute_cy_color(t_scene *scene, t_figures *figure,
// 		t_point ray, double dist, t_point norm, t_point intersect)
// {
// 	// t_point	intersect;
// 	t_point	normal;
// 	t_point	direction;
// 	t_color new_color;
// 	t_color true_color;	
// 	double	rgb[3];

// 	ft_memset(rgb, 0, 3 * sizeof(double));
// 	get_cy_coord(figure, &intersect);
// 	(void)ray;
// 	(void)dist;
// 	// intersect = vector_add(scene->camera->pos, vector_nmultiply(ray, dist));
// 	normal = norm;
// 	get_cy_coord(figure, &normal);
// 	normal = vector_subtract(normal, figure->fig.cy.coord);
// 	normalize2(&normal, normal);
// 	direction = normalize(vector_subtract(scene->light->coord, intersect));
// 	// add_coeficient(&rgb, scene->a_light, scene->al_color.mix);
// 	if (!figure->in_dot)//&& !check_shadow(scene, intersect, figure))
// 	{
// 		// add_coeficient(&rgb, vcos(normal, direction) * scene->light->bri,
// 		// 	scene->light->color.mix);
// 		// add_coeficient(&rgb, get_specular(scene, normal, intersect),
// 		// 	scene->light->color.mix);
// 		double how = vec_scalar_mult(normal, direction);
// 		new_color.r = true_color.r * (0.2) + true_color.r  * (how *  0.8);
// 		new_color.g = true_color.g * (0.2) + true_color.g *  (how * 0.8);
// 		new_color.b = true_color.b * (0.2) + true_color.b * (how * 0.8);
// 		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);

// 	}
// 	else
// 	{
// 		new_color.r = true_color.r * (0.2);
// 		new_color.g = true_color.g * (0.2);
// 		new_color.b = true_color.b * (0.2);
// 		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
// 	}
// 	return (new_color);
// }
