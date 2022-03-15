#include "miniRT.h"

double	get_dot(t_point point1, t_point point2)
{
	return (point1.x * point2.x + point1.y * point2.y + point1.z * point2.z);
}

double	get_module(t_point point1, t_point point2)
{
	return (sqrt(get_dot(point1, point2)));
}

t_point	normalize(t_point point)
{
	t_point	normalized_vector;
	double		module;

	module = get_module(point, point);
	normalized_vector.x = point.x / module;
	normalized_vector.y = point.y / module;
	normalized_vector.z = point.z / module;
	return (normalized_vector);
}
