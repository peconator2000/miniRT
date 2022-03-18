#include "miniRT.h"

//sphere_ray(&min_t, &min_color, dot, elems->fig.sp);
void sphere_ray(double *min_t, int *min_color, t_point dot, t_figures *elem)
{
	double		cur_t;
	double		discr;
	double		rad;

	rad = elem->fig.sp.diameter * 0.5;
	discr = get_discr_sp(elem->fig.sp.coord, dot, rad);
	if (discr < 0)
		return ;
	cur_t = get_min_root(discr, elem->fig.sp.coord, dot, rad);
	if (*min_t == -1 || cur_t < *min_t)
	{
		*min_t = cur_t;
		*min_color = elem->color.mix;
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
