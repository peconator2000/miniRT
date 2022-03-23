#include "miniRT.h"

//sphere_ray(&min_t, &min_color, dot, elems->fig.sp);
void sphere_ray(double *min_t, t_color *min_color, t_point dot, t_figures *elem, t_point sp_dot, t_light *ligth)
{
	double		cur_t;
	double		discr;
	double		rad;
	// t_point		sp_dot;

	rad = elem->fig.sp.newdi * 0.5;
	discr = get_discr_sp(elem->fig.sp.newcoord, dot, rad);
	// printf("discr = %f\n", discr);
	if (discr < 0)
	{
		printf("blc\n");
		return ;
	}
	cur_t = get_min_root(discr, elem->fig.sp.newcoord, dot, rad);
	// printf("root = %f\n", cur_t);
	if ((*min_t == -1 || cur_t < *min_t) && cur_t > 1)
	{
		// printf("zashel\n");
		*min_t = cur_t;
		*min_color = elem->color;
		// printf("elem->color.r = %d elem->color.g = %d elem->color.b = %d\n", (*min_color).r, (*min_color).g, (*min_color).b);
		// printf("dot.x = %f, dot.y = %f cur_t = %f\n", dot.x, dot.y, cur_t);
		// printf("min_t = %f dot.x = %f dot.y = %f dot.z = %f\n", *min_t ,sp_dot.x, sp_dot.y, sp_dot.z);
		vec_mult_num(&sp_dot, (*min_t));
		// (void)ligth;
		// printf("tut\n");
		*min_color = get_ligth_sphere(elem, sp_dot, *min_color, ligth);
		// printf("ne  tut\n");
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
