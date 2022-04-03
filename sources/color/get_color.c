#include "miniRT.h"

void	fill_color(t_color *col, int r, int g, int b)
{
	(*col).r = r;
	(*col).g = g;
	(*col).b = b;
	(*col).mix = (((*col).r << 16) | ((*col).g << 8) | (*col).b);
}

// void camera_diff(t_point *dot, t_camera *cam)
// {
// 	(*dot).x -= cam->pos.x;
// 	(*dot).y -= cam->pos.y;
// 	(*dot).z -= cam->pos.z;
// }


// static void	get_dist_to_obj(t_scene *scene, t_point ray, double *closest_intersection)
// {
// 	double		dist;
// 	t_figures	*figs;

// 	figs = scene->figs;
// 	dist = INFINITY;
// 	while (figs)
// 	{
// 		if (figs->type == SPHERE)
// 			dist = sphere_intersect(scene->light->coord, ray, figs);
// 		else if (figs->type == PLANE)
// 			dist = plane_intersect(scene->light->coord, ray, figs);
// 		if (dist > EPSILON && dist < *closest_intersection)
// 			*closest_intersection = dist;
// 		figs = figs->next;
// 	}
// }

// static int	check_shadow(t_scene *scene, t_point intersect, t_figures *figure)
// {
// 	t_point	ray;
// 	double	ray_len;
// 	double	dist;

// 	ray = vector_subtract(intersect, scene->light->coord);
// 	ray_len = get_module(ray, ray);
// 	ray = normalize(ray);
// 	dist = INFINITY;
// 	get_dist_to_obj(scene, ray, &dist);
// 	if (dist > EPSILON && dist < ray_len - EPSILON && figure->type != -1)
// 		return (1);
// 	return (0);
// }

t_color get_minimal_color(t_minirt *data, t_point dot)
{
	double		min_t;
	t_color		min_color;
	t_figures	*elems;

	elems = data->scene->figs;
	min_t = -1;
	fill_color(&min_color, 0, 0, 0);//инициализируем черным цветом
	while (elems)
	{
		if (elems->type == PLANE)
			is_plane(data->scene, dot, &min_color, &min_t, elems);
		if (elems->type == SPHERE)
			is_sphere(data->scene, dot, &min_color, &min_t, elems);
		if (elems->type == CYLINDER)
			is_cylinder(data->scene, dot, &min_color, &min_t, elems);
		elems = elems->next;
	}
	return (min_color);//текущий
}

int get_color(t_minirt *data, double x_sc, double y_sc)
{
	t_color color;
	t_point	dot;

	get_inscreen(data->scene, &dot, x_sc, y_sc);// x', y', z'
	// printf("dot on local system (%f, %f, %f)\n", dot.x, dot.y, dot.z);
	get_new_coords(data->scene->camera, &dot);//Ax, Ay, Az
	// printf("dot on world system (%f, %f, %f)\n", dot.x, dot.y, dot.z);
	color = get_minimal_color(data, dot);
	return (color.mix);
}
