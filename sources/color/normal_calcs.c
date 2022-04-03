#include "miniRT.h"

t_point	get_normal(t_figures *figure, t_point intersect, t_point ray)
{
	t_point	normal;

	normal = point_define(0, 0, 0);
	if (figure->type == SPHERE)
		normal = normalize(vector_subtract(intersect, figure->fig.sp.coord));
	else if (figure->type == PLANE)
		normal = normalize(figure->no_vec);
	if (get_dot(normal, ray) > 0)
	{
		normal.x *= -1;
		normal.y *= -1;
		normal.z *= -1;
	}
	return (normal);
}
