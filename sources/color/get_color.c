#include "miniRT.h"

t_color get_minimal_color(t_minirt *data, t_point dot)
{
	t_figures	*elems;
	double		min_t;//минимальный параметр
	t_color			min_color;//минимальный цвет соответствующий минимальному параметру
	t_point cur_dot;

	elems = data->scene->figs;
	while (elems)
	{
		min_t = -1;
		min_color.r = 0;
		min_color.g = 0;
		min_color.b = 0;
		min_color.mix = 0;
		if (elems->type == SPHERE)
		{
			// get_scene_point(&(elems->fig.sp.newcoord), data->scene, min_x, max_y);
			new_basis_coordinates(&(elems->fig.sp.newcoord), elems->fig.sp.coord, data->scene->camera);
			elems->fig.sp.newcoord.z = (elems->fig.sp.coord.z * data->scene->camera->view_size[0] * pow(data->scene->resolution[0], -1));// * (-1));
			elems->fig.sp.newdi = elems->fig.sp.diameter * data->scene->camera->view_size[0] * pow(data->scene->resolution[0], -1);
			// printf("old = [%f, %f, %f], new = [%f, %f, %f], newdi = %f\n", elems->fig.sp.coord.x, elems->fig.sp.coord.y, elems->fig.sp.coord.z, elems->fig.sp.newcoord.x, elems->fig.sp.newcoord.y, elems->fig.sp.newcoord.z, elems->fig.sp.newdi);
			// vec_fill(&cur_dot, data->scene->camera->dir.x, data->scene->camera->dir.y, data->scene->camera->dir.z);
			vec_fill(&cur_dot, dot.x, dot.y, dot.z);
			// printf("ligth.x = %f, ligth.y = %f, ligth.z = %f\n", data->scene->light->newcoord.x, data->scene->light->newcoord.y, data->scene->light->newcoord.z);
			sphere_ray(&min_t, &min_color, dot, elems, cur_dot, data->scene->light);
		}
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
