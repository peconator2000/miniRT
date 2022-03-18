#include "miniRT.h"

double	get_discr_sp(t_point cen, t_point ve, double rad)
{
	double	b_2;
	double	ac_4;

	b_2 = pow(2 * ve.x * cen.x + 2 * ve.y * cen.y + 2 * ve.z * cen.z, 2);
	ac_4 = 4 * (pow(ve.x, 2) + pow(ve.y, 2) + pow(ve.z, 2));
	ac_4 = ac_4 * (pow(cen.x, 2) + pow(cen.y, 2) + pow(cen.z, 2) - pow(rad, 2));
	return (b_2 - ac_4);
}

double get_root(double sq_dis, t_point cen, t_point ve, double rad)
{
	double a;
	double b;
	double c;

	a = pow(ve.x, 2) + pow(ve.y, 2) + pow(ve.z, 2);
	b = (2 * ve.x * cen.x + 2 * ve.y * cen.y + 2 * ve.z * cen.z) * (-1);
	c = pow(cen.x, 2) + pow(cen.y, 2) + pow(cen.z, 2) - pow(rad, 2);
	return ((b * (-1) + sq_dis) * pow(2 * a * c, -1));
}

double	get_min_root(double dis, t_point cen, t_point ve, double rad)
{
	double root1;
	double root2;

	root1 = get_root(sqrt(dis), cen, ve, rad);
	root2 = get_root(-sqrt(dis), cen, ve, rad);
	if (root1 > root2)
		return (root2);
	else if (root1 < root2)
		return (root1);
	return(root1);
}

