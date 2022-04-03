#include "miniRT.h"

double	sphere_intersect(t_point src_coord,t_point ray, t_figures *figure)
{
	t_sphere	sphere;
	t_point		src_to_sp;
	double		b;
	double		c;
	double		discr;
	double		radius;

	radius = sphere.diameter * 0.5;
	sphere = figure->fig.sp;
	src_to_sp = vector_subtract(src_coord, sphere.coord);
	b = get_dot(src_to_sp, ray);
	c = get_dot(src_to_sp, src_to_sp) - radius * radius;
	discr = b * b - c;
	if (discr < 0)
		return (0);
	return (-b - sqrtf(discr));
}

double	s_intersect(t_point src_coord,t_point ray, t_figures *sphere)
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	t_min = -1;
	double	discr;
	t_point	sp_dot;
	t_point	op = ray;
	// t_point p = sphere->fig.sp.coord;
	t_point	o = src_coord;
	t_point	s = sphere->fig.sp.coord;//центр сферы
	double	rad = sphere->fig.sp.diameter * 0.5;//радиус

	// op.x = p.x - o.x;
	// op.y = p.y - o.y;
	// op.z = p.z - o.z;
	a = op.x * op.x + op.y * op.y + op.z * op.z;
	b = 2 * (op.x * (o.x - s.x) + op.y * (o.y - s.y) + op.z * (o.z - s.z));
	c = ((o.x - s.x) * (o.x - s.x) + (o.y - s.y) * (o.y - s.y) + (o.z - s.z) * (o.z - s.z) - rad * rad);
	discr = b * b - 4 * a * c;
	t1 = (b * (-1) + sqrt(discr)) / (2 * a);
	t2 = (b * (-1) - sqrt(discr)) / (2 * a);
	if (t1 >= 1 || t2 >= 1)
	{
		if (t1 >= 1 && t2 >= 1)
		{
			if (t1 < t2)
				t_min = t1;
			else
				t_min = t2;
		}
		else
		{
			if (t1 >= 1)
				t_min = t1;
			else
				t_min = t2;
		}
	}
	else
		return (0.00000);
	sp_dot.x = op.x * t_min + o.x;
	sp_dot.y = op.y * t_min + o.y;
	sp_dot.z = op.z * t_min + o.z;
	return (t_min);
}
