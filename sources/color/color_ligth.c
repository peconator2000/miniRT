#include "miniRT.h"

double epsi = 0.0000001;

// int cy_shad(t_minirt *data, t_ray ray, t_point k)
// {
// 	double		min_t;
// 	// t_color		min_color;
// 	t_figures	*elems;

// 	elems = data->scene->figs;
// 	min_t = -1;
// 	while (elems)
// 	{
// 		if (elems->type == PLANE)
// 			min_t = is_cy_plane(ray, elems, k);
// 		if (elems->type == SPHERE)
// 			min_t = is_cy_sphere(ray, elems, k);
// 		if (elems->type == CYLINDER)
// 			min_t = is_cylinder(ray.o, ray.p, elems);
// 		elems = elems->next;
// 		if (min_t > 1)
// 			return (1);
// 	}
// 	return (0);
// }

// int is_shad(t_minirt *data, t_figures *fig, t_ray ray)
// {
// 	double		min_t;
// 	t_color		min_color;
// 	t_figures	*elems;

// 	elems = data->scene->figs;
// 	min_t = -1;
// 	if (fig->type == CYLINDER)
// 		return (cy_shad(data, ray, fig->fig.cy.coord));
// 	fill_color(&min_color, 0, 0, 0);
// 	while (elems)
// 	{
// 		if (elems->type == PLANE)
// 			min_t = is_plane(ray, elems);
// 		if (elems->type == SPHERE)
// 			min_t = is_sphere(ray, elems);
// 		if (elems->type == CYLINDER)
// 			min_t = is_cylinder(ray.o, ray.p, elems);
// 		elems = elems->next;
// 		if (min_t > 1)
// 			return (1);
// 	}
// 	return (0);
// }

t_color get_ligth(t_ray v1, t_ray v2, t_figures *elem, t_color true_color, t_light *light, t_minirt *data)
{
	double how;
	t_color new_color;
	// t_light *light;

	how = vec_scalar_mult(v1.op, v2.op);
	// normalize2(&(v1.op), v1.op);
	// show_vec("norm ", v2.op);
	// show_vec("dir = ", v1.op);
	(void)data;
	if (how < 0 || elem->in_dot)// || is_shad(data, elem, v1))
	{
		new_color.r = true_color.r * (0.2);
		new_color.g = true_color.g * (0.2);
		new_color.b = true_color.b * (0.2);
		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);

		return (new_color);
	}
	(void)elem;
	new_color.r = true_color.r * (0.2) + true_color.r * light->color.r * (how *  light->bri * pow(255, -1));
	new_color.g = true_color.g * (0.2) + true_color.g * light->color.g * (how * light->bri * pow(255, -1));
	new_color.b = true_color.b * (0.2) + true_color.b * light->color.b * (how * light->bri * pow(255, -1));
	new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
	return (new_color);
}

t_color get_ligth_sphere(t_figures *elem, t_point dot, t_color true_color, t_light *ligth, t_minirt *data)
{
	t_point lig;
	t_point	cen;
	t_ray l_dist;
	t_ray	norm;

	lig = ligth->coord;
	cen = elem->fig.sp.coord;
	ray_fill(&l_dist, dot, lig);
	ray_fill(&norm, cen, dot);
	normalize2(&(l_dist.op), l_dist.op);
	normalize2(&(norm.op), norm.op);
	return (get_ligth(l_dist, norm, elem, true_color, ligth, data));
}


t_color get_ligth_cylinder(t_figures *elem, t_point dot, t_ray norm, t_color true_color, t_light *ligth, t_minirt *data)
{
	t_point lig;
	t_ray l_dist;

	lig = ligth->coord;
	get_cy_basis_dot(lig, &lig, elem, elem->fig.cy.coord);//new
	// get_cy_basis_dot(lig, &lig, elem->r, elem->u, elem->d, elem->fig.cy.coord);
	ray_fill(&l_dist, dot, lig);
	normalize2(&(l_dist.op), l_dist.op);
	// printf("stranno\n");
	return (get_ligth(l_dist, norm, elem, true_color, ligth, data));
}

t_color get_ligth_plane(t_figures *elem, t_point dot, t_color true_color, t_light *ligth, t_minirt *data)
{
	t_point lig;
	t_ray	l_dist;
	t_ray	norm;

	lig = ligth->coord;
	ray_fill(&l_dist, dot, lig);
	vec_fill(&(norm.o), 0, 0, 0);
	vec_fill(&(norm.p), elem->no_vec.x, elem->no_vec.y, elem->no_vec.z);
	ray_fill(&(norm), norm.o, norm.p);
	normalize2(&(l_dist.op), l_dist.op);
	normalize2(&(norm.op), norm.op);
	return (get_ligth(l_dist, norm, elem, true_color, ligth, data));
}


