#include "miniRT.h"

double eps = 0.000001;

// void	draw_sphere(t_minirt *data, t_sphere *sp, int wid, int hig)
// {
// 	int	x;
// 	int y;
// 	double min_x;
// 	double max_y;
// 	double mid;
// 	t_point view;//точка на экране обзора
// 	// TODO
// 	(void)sp;
// 	y = -1;
// 	vec_fill(&view, 0, 0, 0);
// 	get_new_basis(data->scene);
// 	min_x = data->scene->resolution[0] * (-0.5);
// 	max_y = data->scene->resolution[1] * (0.5);
// 	mid = min_x;
// 	t_point newc = data->scene->figs->fig.sp.coord;
// 	printf("hig = %d wid = %d\ncenter OF SPHERE x = %f  y = %f  z = %f\n",hig, wid, newc.x, newc.y, newc.z);
// 	printf("napravlenie camery = [%f, %f, %f]\n", data->scene->camera->no_vec.x, data->scene->camera->no_vec.y, data->scene->camera->no_vec.z);
// 	while (++y < hig)
// 	{
// 		x = -1;
// 		min_x = mid;
// 		while (++x < wid)
// 		{
// 			get_scene_point(&view, data->scene, min_x, max_y);
// 			new_basis_coordinates(&view, view, data->scene->camera);
// 			my_mlx_pixel_put(data->img, x, y, get_color(data, view));
// 			min_x++;
// 		}
// 		max_y--;
// 	}
// 	printf("view wi = %f view hi = %f\n", data->scene->camera->view_size[0], data->scene->camera->view_size[1]);
// }

void draw_all(t_minirt *data, int wid, int hig)
{
	int		x_pix;
	int		y_pix;
	double	x_sc;
	double	y_sc;

	y_pix = 0;
	y_sc = hig * (0.5);
	new_basis(data->scene);
	printf("rigth = (%f, %f, %f)\n", data->scene->camera->rigth.x, data->scene->camera->rigth.y, data->scene->camera->rigth.z);
	printf("up = (%f, %f, %f)\n", data->scene->camera->up.x, data->scene->camera->up.y, data->scene->camera->up.z);
	printf("dir = (%f, %f, %f)\n", data->scene->camera->dir.x, data->scene->camera->dir.y, data->scene->camera->dir.z);
	while (y_pix < hig)
	{
		x_pix = 0;
		x_sc = wid * (-0.5);
		while (x_pix < wid)
		{
			my_mlx_pixel_put(data->img, x_pix, y_pix, get_color(data, x_sc, y_sc));
			x_pix += 1;
			x_sc += 1;
		}
		y_pix += 1;
		y_sc -= 1;
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
	draw_all(data, wid, hig);//посылаем туда конкретную сферу
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (1);
}
