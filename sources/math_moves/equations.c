#include "miniRT.h"

double	get_discr_sp(t_point cen, t_point ve, double rad)
{
	double	b_2;
	double	ac_4;

	b_2 = pow(2 * ve.x * cen.x + 2 * ve.y * cen.y + 2 * ve.z * cen.z, 2);
	ac_4 = 4 * (pow(ve.x, 2) + pow(ve.y, 2) + pow(ve.z, 2));
	ac_4 = ac_4 * (pow(cen.x, 2) + pow(cen.y, 2) + pow(cen.y, 2));
	return (b_2 - ac_4);
}