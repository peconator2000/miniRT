#include "miniRT.h"

//sphere_ray(&min_t, &min_color, dot, elems->fig.sp);




void sphere_ray(double *min_t, int *min_color, t_point dot, t_figures *elem)
{
	double		cur_t;
	double		discr;
	double		rad;//
	// (void)min_t;
	// (void)min_color;
	// (void)dot;
	// (void)sp;

	rad = elem->fig.sp.diameter * 0.5;
	discr = get_discr_sp(elem->fig.sp.coord, dot, rad);
	if (discr < 0)
		return ;
	cur_t = get_min_root();
	if (*min_t == -1 || cur_t < *min_t)
	{
		*min_t = cur_t;
		*min_color = elem->color.mix;
	}
	return (1);
}