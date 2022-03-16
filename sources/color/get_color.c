#include "miniRT.h"

int get_minimal_color(t_minirt *data, t_point dot)
{
	t_figures	*elems;
	int			min_t;//минимальный параметр
	int			min_color;//минимальный цвет соответствующий минимальному параметру

	// min_t = 0;
	// min_color = 0;
	// elems = data->scene->figs;
	// while (elems)
	// {
	// 	if (elems->type == 1)//sphere
	// 		sphere_ray(&min_t, &min_color, dot, elems->fig.sp);
	// 	else if (elems->type == 2)//plane
	// 		plane_ray(&min_t, &min_color, dot, elems->fig.pl);
	// 	else if (elems->type == 3)//cylinder
	// 		cylinder_ray(&min_t, &min_color, dot, elems->fig.cy);
	// 	elems = elems->next;
	// }
	
	sphere_ray(&min_t, &min_color, dot, &(elems->fig.sp));
	return (elems->color);//текущий
}

int get_color(t_minirt *data, t_point dot)//тут будет учет теней, глубины, света и тд
{
	int color;

	//функция, которая проходится по всем фигурам из списка, ищет пересечения, сохраняет минимальный параметр
	//и возвращает цвет той фигуры, которая соответствует минимальному параметру
	//эта функция выводит плоские фигуры
	color = get_minimal_color(data, dot);

}