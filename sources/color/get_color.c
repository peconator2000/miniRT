#include "miniRT.h"

void	fill_color(t_color *col, int r, int g, int b)
{
	(*col).r = r;
	(*col).g = g;
	(*col).b = b;
	(*col).mix = (((*col).r << 16) | ((*col).g << 8) | (*col).b);
}

void	get_sphere_param(double *min_t, t_color *min_color, t_figures *sp, t_scene *sc, t_ray ray)
{
	t_point		sp_dot;
	double		t;

	t = is_sphere(ray, sp);
	if (((*min_t) == -1 || t < *min_t) && t != -1)
	{
		(*min_t) = t;
		(*min_color) = sp->color;
		get_ray_dot(&sp_dot, ray, *(min_t));
		(*min_color) = compute_color(sc, sp, ray.op, t);
	}
}

void	get_plane_param(double *min_t, t_color *min_color, t_figures *pl, t_scene *sc, t_ray ray)
{
	t_point		pl_dot;
	double		t;

	t = is_plane(ray, pl);
	if (((*min_t) == -1 || t < *min_t) && t > 1)
	{
		(*min_t) = t;
		(*min_color) = pl->color;
		get_ray_dot(&pl_dot, ray, *(min_t));
		(*min_color) = compute_color(sc, pl, ray.op, t);
	}
}


void	get_cylinder_param(double *min_t, t_color *min_color, t_figures *cy, t_scene *sc, t_point dot)
{
	t_ray		new_ray;
	t_point		cy_dot;
	t_point		norm;
	double		t;

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

		aha = norm;
		(*min_color) = compute_color(sc, cy, new_ray.op, t);
	}
}

t_color get_minimal_color(t_minirt *data, t_point dot)
{
	double		min_t;
	t_color		min_color;
	t_figures	*elems;
	t_ray ray;

	elems = data->scene->figs;
	min_t = -1;
	fill_color(&min_color, 0, 0, 0);//инициализируем черным цветом
	while (elems)
	{
		ray_fill(&ray, data->scene->camera->pos, dot);
		if (elems->type == PLANE)
			get_plane_param(&min_t, &min_color, elems, data->scene, ray);
		if (elems->type == SPHERE)
			get_sphere_param(&min_t, &min_color, elems, data->scene, ray);
		if (elems->type == CYLINDER)
			// is_cylinder(data->scene, dot, &min_color, &min_t, elems);//old
			get_cylinder_param(&min_t, &min_color, elems, data->scene, dot);//new
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
