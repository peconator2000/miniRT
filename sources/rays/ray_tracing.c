#include "miniRT.h"

//sphere_ray(&min_t, &min_color, dot, elems->fig.sp);
void sphere_ray(double *min_t, t_color *min_color, t_point dot, t_figures *elem, t_point sp_dot, t_light *ligth)
{
	double		cur_t;
	double		discr;
	double		rad;
	// t_point		sp_dot;

	rad = elem->fig.sp.diameter * 0.5;
	// printf("dot = [%f, %f, %f]\n", dot.x, dot.y, dot.z);
	discr = get_discr_sp(elem->fig.sp.coord, dot, rad);
	// printf("centre = (%f, %f, %f)\n", elem->fig.sp.coord.x,  elem->fig.sp.coord.y,  elem->fig.sp.coord.z);
	// printf("discr = %f\n", discr);
	if (discr < 0)
	{
		// printf("blc\n");
		return ;
	}
	cur_t = get_min_root(discr, elem->fig.sp.coord, dot, rad);
	// printf("rad = [%f, %f, %f] cur_t = %f\n", elem->fig.sp.coord.x, elem->fig.sp.coord.y, elem->fig.sp.coord.z, cur_t);
	if ((*min_t == -1 || cur_t < *min_t))// && cur_t > 1)
	{
		*min_t = cur_t;
		*min_color = elem->color;
		vec_mult_num(&sp_dot, (*min_t));
		// printf("GET DOT = [%f, %f, %f]\n", sp_dot.x, sp_dot.y, sp_dot.z);
		(void)ligth;
		*min_color = get_ligth_sphere(elem, sp_dot, *min_color, ligth);
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
