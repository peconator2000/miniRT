#include "miniRT.h"

double epsi = 0.0000001;

t_color get_ligth(t_point v1, t_point v2, t_figures *elem, t_color true_color)
{
	double how;
	t_color new_color;
	t_light *light;
	double	part;

	how = vec_scalar_mult(v1, v2);
	light = elem->fig.scene->light;
	printf("how = %f\n", how);
	// if (how <= epsi || true_color.mix == 0)
	// 	return (true_color);
	part = pow(true_color.r + true_color.g + true_color.b, -1);
	new_color.r = true_color.r;// + light->color.r * (how + light->bri) * part;// * how * part * true_color.r;// + light->color.r * how * light->bri;//* (light->color.r + (how * light->bri));
	new_color.g = true_color.g;// + light->color.g * (how + light->bri) * part;// + light->color.g * how * light->bri;//* (light->color.g + (how * light->bri));
	new_color.b = true_color.b;// + light->color.b * (how + light->bri) * part;// + light->color.b * how * light->bri;//+ (how * light->bri) * light->color.b);//* (light->color.b + (how * light->bri));
	new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);// * light->bri;
	return (new_color);
}

t_color get_ligth_sphere(t_figures *elem, t_point dot, t_color true_color)
{
	t_point lig;//координаты света
	t_point	cen;//координаты центра сферы
	t_point l_dist;//расстояние от центра сферы до света
	t_point	norm;//нормаль к точке

	lig = elem->fig.scene->light->coord;
	cen = elem->fig.sp.coord;
	vec_fill(&l_dist, lig.x - dot.x, lig.y - dot.y, lig.z - dot.z);//заполняем вектор расстояния до центра сферы
	vec_fill(&norm, dot.x - cen.x, dot.y - cen.y, dot.z - cen.z);//заполняем вектор нормы
	normalize2(&l_dist, l_dist);//нормируем
	normalize2(&norm, norm);//нормируем
	return (get_ligth(l_dist, norm, elem, true_color));
}