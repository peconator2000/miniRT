#include "miniRT.h"

double eps = 0.000001;

int	pixel_in_sp(t_sphere *sp, int x, int y)
{
	double new_x;
	double new_y;
	double new_rad;

	new_x = x - sp->coord.x;
	new_y = y - sp->coord.y;
	new_rad = sqrt(new_x * new_x + new_y * new_y);
	if ((new_rad - (sp->diameter * 0.5)) < eps)
		return (1);
	return (0);
}

// void draw_pixel(t_minirt *data, int x, int y, int draw)
// {
// 	if (draw)
// 		my_mlx_pixel_put(data->img, x, y, 0xffb6c1);
// 	else
// 		my_mlx_pixel_put(data->img, x, y, 0);
// }

void	draw_sphere(t_minirt *data, t_sphere *sp, int wid, int hig)
{
	int	x;
	int y;
	double min_x;
	double max_y;
	double mid;
	t_point view;//точка на экране обзора

	// TODO
	(void)sp;
	y = -1;
	vec_fill(&view, 0, 0, 0);//убрать?
	// printf("in drawsph1\n");
	get_new_basis(data->scene);//получаем новый базис
	// printf("in drawsph2\n");
	min_x = data->scene->resolution[0] * (-0.5);
	max_y = data->scene->resolution[1] * (0.5);
	mid = min_x;
	t_point newc = data->scene->figs->fig.sp.coord;
	printf("hig = %d wid = %d\ncenter OF SPHERE x = %f  y = %f  z = %f\n",hig, wid, newc.x, newc.y, newc.z);
	printf("napravlenie camery = [%f, %f, %f]\n", data->scene->camera->no_vec.x, data->scene->camera->no_vec.y, data->scene->camera->no_vec.z);
	while (++y < hig)
	{
		x = -1;
		min_x = mid;
		while (++x < wid)
		{
			get_scene_point(&view, data->scene, min_x, max_y);
			new_basis_coordinates(&view, view, data->scene->camera);//поворачиваем сцену по вектору direction, теперь view - радиус-вектор
			// printf("minx_z = %f max_y = %f\n", min_x, max_y);
			// if (fabs(min_x - newc.x) < 0.0000001 && fabs(max_y - newc.y) < 0.0000001)
			// {
			// 	printf("new center OF SPHERE x = %f  y = %f  z = %f\n", view.x, view.y, view.z);
			// 	printf("x = %d, y = %d\n", x, y);
			// }
			my_mlx_pixel_put(data->img, x, y, get_color(data, view));
			min_x++;
		}
		max_y--;
	}
	printf("view wi = %f view hi = %f\n", data->scene->camera->view_size[0], data->scene->camera->view_size[1]);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	int		offset;
	char	*c;

	offset = (y * img->line_length) + (x * img->bits_per_pixel / 8);
	c = img->addr + offset;
	*(unsigned int *)c = color;
}

int	draw_figures(t_minirt *data)
{
	int wid;
	int hig;

	wid = data->scene->resolution[0];
	hig = data->scene->resolution[1];
	draw_sphere(data, &(data->scene->figs->fig.sp), wid, hig);//посылаем туда конкретную сферу
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (1);
}
