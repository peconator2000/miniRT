#include "miniRT.h"

int get_minimal_color(t_minirt *data, t_point dot)
{
	t_figures	*elems;
	double		min_t;//минимальный параметр
	int			min_color;//минимальный цвет соответствующий минимальному параметру

	min_t = 0;
	min_color = 0;
	elems = data->scene->figs;
	// printf("[in get_min_color] after cycle\n");
	// printf("type = %d", elems->type);
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
	// printf("[in get_min_color] before cycle\n");
	// printf("")
	// sphere_ray(&min_t, &min_color, dot, elems);
	// if (min_color!= 0)
	// 	printf("nashli cvet\n");
	return (min_color);//текущий
}

int get_color(t_minirt *data, t_point dot)//тут будет учет теней, глубины, света и тд
{
	int color;

	//функция, которая проходится по всем фигурам из списка, ищет пересечения, сохраняет минимальный параметр
	//и возвращает цвет той фигуры, которая соответствует минимальному параметру
	//эта функция выводит плоские фигуры
	color = get_minimal_color(data, dot);
	// printf("[in get_color] color = %d\n", color);
	return (color);
}
