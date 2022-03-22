#include "miniRT.h"

//sphere_ray(&min_t, &min_color, dot, elems->fig.sp);
void sphere_ray(double *min_t, t_color *min_color, t_point dot, t_figures *elem)
{
	double		cur_t;
	double		discr;
	double		rad;
	t_point		sp_dot;

	rad = elem->fig.sp.diameter * 0.5;
	discr = get_discr_sp(elem->fig.sp.coord, dot, rad);
	// printf("discr = %f\n", discr);
	if (discr < 0)
		return ;
	cur_t = get_min_root(discr, elem->fig.sp.coord, dot, rad);
	if ((*min_t == -1 || cur_t < *min_t))// && cur_t > 1)
	{
		*min_t = cur_t;
		*min_color = elem->color;
		vec_fill(&sp_dot, elem->fig.scene->camera->dir.x * (*min_t) + elem->fig.scene->camera->new_pos.x,
		elem->fig.scene->camera->dir.y * (*min_t) + elem->fig.scene->camera->new_pos.y, 
		elem->fig.scene->camera->dir.z * (*min_t) + elem->fig.scene->camera->new_pos.z);
		// printf("min_t = %f dot.x = %f dot.y = %f dot.z = %f\n", *min_t ,sp_dot.x, sp_dot.y, sp_dot.z);
		*min_color = get_ligth_sphere(elem, sp_dot, *min_color);
	}
}

int	plane_ray(int *min_t, int *min_color, t_point dot, t_plane *pl)
{
	(void)min_t;
	(void)min_color;
	(void)dot;
	(void)pl;
	return (0);
}

int			cylinder_ray(int *min_t, int *min_color, t_point dot, t_cylinder *cy)
{
	(void)min_t;
	(void)min_color;
	(void)dot;
	(void)cy;
	return (0);
}
