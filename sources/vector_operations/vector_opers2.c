#include "miniRT.h"

t_point	point_define(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point	vector_add(t_point start, t_point end)
{
	t_point	result_point;

	result_point.x = start.x + end.x;
	result_point.y = start.y + end.y;
	result_point.z = start.z + end.z;
	return (result_point);
}

t_point	vector_substract(t_point start, t_point end)
{
	t_point	result_point;

	result_point.x = start.x - end.x;
	result_point.y = start.y - end.y;
	result_point.z = start.z - end.z;
	return (result_point);
}

t_point	vector_cross(t_point start, t_point end)
{
	t_point	cross_point;

	cross_point.x = start.y * end.z - start.z * end.y;
	cross_point.y = start.z * end.x - start.x * end.z;
	cross_point.z = start.x * end.y - start.y * end.x;
	return (cross_point);
}
