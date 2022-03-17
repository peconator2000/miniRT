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
	t_point view;//точка на экране обзора

	// TODO
	(void)sp;
	y = -1;
	vec_fill(&view, 0, 0, 0);//убрать?
	get_new_basis(data->scene);//получаем новый базис
	while (++y < hig)
	{
		x = -1;
		while (++x < wid)
		{
			get_scene_point(&view, data->scene, x, y);//получаем точку на экране обзора
			new_basis_coordinates(&view, view, data->scene->camera);//поворачиваем сцену по вектору direction, теперь view - радиус-вектор
			my_mlx_pixel_put(data->img, x, y, get_color(data, view));
		}
	}
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
