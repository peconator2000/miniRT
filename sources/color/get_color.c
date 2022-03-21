#include "miniRT.h"

t_color get_minimal_color(t_minirt *data, t_point dot)
{
	t_figures	*elems;
	double		min_t;//минимальный параметр
	t_color			min_color;//минимальный цвет соответствующий минимальному параметру

	min_t = 0;
	min_color.r = 0;
	min_color.g = 0;
	min_color.b = 0;
	min_color.mix = 0;
	elems = data->scene->figs;
	while (elems)
	{
		if (elems->type == SPHERE)
			sphere_ray(&min_t, &min_color, dot, elems);
		// else if (elems->type == 2)//plane
		// 	plane_ray(&min_t, &min_color, dot, &(elems->fig.pl));
		// else if (elems->type == 3)//cylinder
		// 	cylinder_ray(&min_t, &min_color, dot, &(elems->fig.cy));
		elems = elems->next;
	}
	return (min_color);//текущий
}

int get_color(t_minirt *data, t_point dot)//тут будет учет теней, глубины, света и тд
{
	t_color color;

	//функция, которая проходится по всем фигурам из списка, ищет пересечения, сохраняет минимальный параметр
	//и возвращает цвет той фигуры, которая соответствует минимальному параметру
	//эта функция выводит плоские фигуры
	color = get_minimal_color(data, dot);
	// printf("[in get_color] color = %d\n", color);
	// color.mix = (color.r << 16) | (color.g << 8) | color.b;
	return (color.mix);
}
