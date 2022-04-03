#include "miniRT.h"

double epsi = 0.0000001;

t_color get_ligth(t_point v1, t_point v2, t_figures *elem, t_color true_color, t_light *light)
{
	double how;
	t_color new_color;
	// t_light *light;

	how = vec_scalar_mult(v1, v2);

	if (how < 0)
	{
		new_color.r = true_color.r * (0.2);
		new_color.g = true_color.g * (0.2);
		new_color.b = true_color.b * (0.2);
		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
		return (new_color);
	}
	(void)elem;
	new_color.r = true_color.r * (0.2) + true_color.r * light->color.r * (how *  light->bri * pow(255, -1));
	new_color.g = true_color.g * (0.2) + true_color.g * light->color.g * (how * light->bri * pow(255, -1));
	new_color.b = true_color.b * (0.2) + true_color.b * light->color.b * (how * light->bri * pow(255, -1));
	new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
	return (new_color);
}

t_color get_ligth_sphere(t_figures *elem, t_point dot, t_color true_color, t_light *ligth)
{
	t_point lig;
	t_point	cen;
	t_point l_dist;
	t_point	norm;

	lig.x = ligth->coord.x;
	lig.y = ligth->coord.y;
	lig.z = ligth->coord.z;
	cen = elem->fig.sp.coord;
	vec_fill(&l_dist, lig.x - dot.x, lig.y - dot.y, lig.z - dot.z);
	vec_fill(&norm, dot.x - cen.x, dot.y - cen.y, dot.z - cen.z);
	normalize2(&l_dist, l_dist);
	normalize2(&norm, norm);
	return (get_ligth(l_dist, norm, elem, true_color, ligth));
}


t_color get_ligth_cylinder(t_figures *elem, t_point dot, t_point norm, t_color true_color, t_light *ligth)
{
	t_point lig;
	t_point l_dist;

	lig.x = ligth->coord.x;
	lig.y = ligth->coord.y;
	lig.z = ligth->coord.z;
	get_cy_basis_dot(lig, &lig, elem->r, elem->u, elem->d, elem->fig.cy.coord);
	vec_fill(&l_dist, lig.x - dot.x, lig.y - dot.y, lig.z - dot.z);
	normalize2(&l_dist, l_dist);
	// printf("stranno\n");
	return (get_ligth(l_dist, norm, elem, true_color, ligth));
}

t_color get_ligth_plane(t_figures *elem, t_point dot, t_color true_color, t_light *ligth)
{
	t_point lig;
	t_point l_dist;
	t_point	norm;

	lig.x = ligth->coord.x;
	lig.y = ligth->coord.y;
	lig.z = ligth->coord.z;
	vec_fill(&l_dist, lig.x - dot.x, lig.y - dot.y, lig.z - dot.z);
	vec_fill(&norm, elem->no_vec.x, elem->no_vec.y, elem->no_vec.z);
	normalize2(&l_dist, l_dist);
	normalize2(&norm, norm);
	return (get_ligth(l_dist, norm, elem, true_color, ligth));
}


