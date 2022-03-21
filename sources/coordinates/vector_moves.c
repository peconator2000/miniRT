#include "miniRT.h"

void	vec_equal(t_point *dot1, t_point *dot2) // dot1 становится dot2
{
	(*dot1).x = (*dot2).x;
	(*dot1).y = (*dot2).y;
	(*dot1).z = (*dot2).z;
}

void	vec_fill(t_point *res, double x, double y, double z) // заполнение вектора данными x, y, z
{
	(*res).x = x;
	(*res).y = y;
	(*res).z = z;
}

void	vec_mult_vec(t_point *res, t_point vec1, t_point vec2) // векторное умножение, помещается в res
{
	(*res).x = vec1.y * vec2.z - vec1.z * vec2.y;
	(*res).y = vec2.x * vec1.z - vec1.x * vec2.z;
	(*res).z = vec1.x * vec2.y - vec2.x * vec1.y;
}

void	vec_mult_num(t_point *res, double num)
{
	(*res).x *= num;
	(*res).y *= num;
	(*res).z *= num;
}

double vec_scalar_mult(t_point vec1, t_point vec2)
{
	double x_res;
	double y_res;
	double z_res;

	x_res = vec1.x * vec2.x;
	y_res = vec1.y * vec2.y;
	z_res = vec1.z * vec2.z;
	return (x_res + y_res + z_res);
}
