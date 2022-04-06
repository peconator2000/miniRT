#include "miniRT.h"

t_point	get_normal(t_figures *figure, t_point intersect, t_point ray)
{
	t_point	normal;

	normal = point_define(0, 0, 0);
	if (figure->type == PLANE)
		normal = normalize(figure->no_vec);
	if (figure->type == SPHERE)
		normal = normalize(vector_subtract(intersect, figure->fig.sp.coord));

	if (get_dot(normal, ray) > 0)
		normal = vector_nmultiply(normal, -1);
	(void)ray;
	normal = normalize(normal);
	(void)intersect;
	return (normal);
}
