#include "miniRT.h"

//double	is_sphere(t_ray ray, t_figures *sp)

double get_pl_t(t_point n, t_ray ray, t_point k)
{
	double	num;
	double	den;
	double	d;

	
	d = n.x * k.x + n.y * k.y + n.z * k.z;
	num = d - (n.x * ray.o.x + n.y * ray.o.y + n.z * ray.o.z);
	den = n.x * ray.op.x + n.y * ray.op.y + n.z * ray.op.z;
	if (den == 0)
		return (-1);
	return (num * pow(den, -1));

}

double	is_plane(t_ray ray, t_figures *pl)
{
	t_point n = pl->no_vec;
	t_point k = pl->fig.pl.coord;
	
	return (get_pl_t(n, ray, k));
}