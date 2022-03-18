#include "miniRT.h"

double	get_distance(t_point start, t_point end)
{
	double	distance;

	distance = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2) + pow(end.z - start.z, 2));
	return (distance);
}

double	get_dot(t_point start, t_point end)
{
	return (start.x * end.x + start.y * end.y + start.z * end.z);
}

double	get_module(t_point start, t_point end)
{
	return (sqrt(get_dot(start, end)));
}

t_point	normalize(t_point point)
{
	t_point	normalized_vector;
	double	module;

	module = get_module(point, point);
	normalized_vector.x = point.x / module;
	normalized_vector.y = point.y / module;
	normalized_vector.z = point.z / module;
	return (normalized_vector);
}

void	normalize2(t_point *dot, t_point point)
{
	double	module;

	module = get_module(point, point);
	(*dot).x = point.x / module;
	(*dot).y = point.y / module;
	(*dot).z = point.z / module;
}
