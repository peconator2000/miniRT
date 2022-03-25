#include "miniRT.h"

double epsi = 0.0000001;

t_color get_ligth(t_point v1, t_point v2, t_figures *elem, t_color true_color, t_light *light)
{
	double how;
	t_color new_color;
	// t_light *light;

	how = vec_scalar_mult(v1, v2);
	// light = elem->fig.scene->light;
	// if (how > 0)
	// 	printf("how = %f\n", how);
	// else
	// {
	// 	// return (true_color);
	// 	printf("shade\n");
	// }
	// if (how < 0)
	// {
	// 	new_color.r = 0;
	// 	new_color.g = 0;
	// 	new_color.b = 0;
	// 	new_color.mix = 0;
	// 	return (new_color);
	// }
	if (how < 0)
	{
		new_color.r = true_color.r * (0.2 + how) ;// * how * part * true_color.r;// + light->color.r * how * light->bri;//* (light->color.r + (how * light->bri));
		new_color.g = true_color.g * (0.2 + how);// + light->color.g * how * light->bri;//* (light->color.g + (how * light->bri));
		new_color.b = true_color.b * (0.2 + how);
		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
		return (new_color);
		return (true_color);
	}
	(void)elem;
	new_color.r = true_color.r * light->color.r * (how *  light->bri * pow(255, -1));// * how * part * true_color.r;// + light->color.r * how * light->bri;//* (light->color.r + (how * light->bri));
	new_color.g = true_color.g * light->color.g * (how * light->bri * pow(255, -1));// + light->color.g * how * light->bri;//* (light->color.g + (how * light->bri));
	new_color.b = true_color.b * light->color.b * (how * light->bri * pow(255, -1));// + light->color.b * how * light->bri;//+ (how * light->bri) * light->color.b);//* (light->color.b + (how * light->bri));
	// printf("true_red = %d	true_green = %d		true_blue = %d\n", new_color.r, new_color.g, new_color.b);
	// printf("red = %d	green = %d		blue = %d\n", new_color.r, new_color.g, new_color.b);
	new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);// * light->bri;
	// printf("true_color = %d		new_color = %d\n", true_color.mix, new_color.mix);
	return (new_color);
}

t_color get_ligth_sphere(t_figures *elem, t_point dot, t_color true_color, t_light *ligth)
{
	t_point lig;//координаты света
	t_point	cen;//координаты центра сферы
	t_point l_dist;//расстояние от центра сферы до света
	t_point	norm;//нормаль к точке

	lig.x = ligth->coord.x;
	lig.y = ligth->coord.y;
	lig.z = ligth->coord.z;
	cen = elem->fig.sp.coord;
	vec_fill(&l_dist, lig.x - dot.x, lig.y - dot.y, lig.z - dot.z);//заполняем вектор расстояния до центра сферы
	vec_fill(&norm, dot.x - cen.x, dot.y - cen.y, dot.z - cen.z);//заполняем вектор нормы
	normalize2(&l_dist, l_dist);//нормируем
	normalize2(&norm, norm);//нормируем
	// printf("norm\n");
	return (get_ligth(l_dist, norm, elem, true_color, ligth));
}