#include "miniRT.h"

t_point	get_normal(t_figures *figure, t_point intersect, t_point ray)
{
	t_point	normal;

	normal = point_define(0, 0, 0);
	if (figure->type == PLANE)
		normal = normalize(figure->no_vec);
	else


	if (figure->type == SPHERE)
		normal = normalize(vector_subtract(intersect, figure->fig.sp.coord));

	//=========================================================================================
	// if (figure->type == CYLINDER)
	// {
		// t_point hei_point;
		// double	t;
		// t_point pt;
		// t_point res;

		// hei_point = vector_add(figure->fig.cy.coord, vector_nmultiply(figure->no_vec, figure->fig.cy.height));
		// 	return (vector_nmultiply(figure->no_vec, -1.0));
		// else if (get_module(vector_subtract(intersect, hei_point), vector_subtract(intersect, hei_point)) < figure->fig.cy.diameter / 2)
		// 	return (figure->no_vec);
		// else
		// {
		// 	t = get_dot(vector_subtract(intersect,figure->fig.cy.coord), figure->no_vec);
		// 	pt = vector_add(figure->fig.cy.coord, vector_nmultiply(figure->no_vec, t));
		// 	res = normalize(vector_subtract(intersect, pt));
		// 	return (res);
		// }
		// normal = normalize(point_define(figure->fig.cy.coord.x, figure->fig.cy.coord.y, 0));
		// t_point		n;
		// t_point		v;
		// t_point		temp;
		// t_point		c0;

		// v = vector_subtract(figure->fig.cy.coord, intersect);
		// temp = vector_nmultiply(figure->no_vec, get_dot(v, figure->no_vec));
		// c0 = vector_add(figure->fig.cy.coord, temp);
		// temp = vector_subtract(c0, intersect);
		// n = normalize(temp);
		// normal = n;
	// }
	//=========================================================================================

	if (figure->type != CYLINDER)
		normal = get_dot(normal, ray) > 0 ? vector_nmultiply(normal, -1) : normal;
	else
	{
		normal = aha;
	}

	if (figure->type == CYLINDER && get_dot(normal, ray) > 0)
	{
		normal = vector_nmultiply(normal, -1);
		// printf("normal.x = %f, normal.y = %f, normal.z = %f\n", normal.x, normal.y, normal.z);
	}

	(void)ray;
	normal = normalize(normal);
	(void)intersect;
	return (normal);
}
