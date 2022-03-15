#include "miniRT.h"

double eps = 0.000001;

int pixel_in_sp(t_sphere *sp, int x, int y)
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

void draw_pixel(t_minirt *data, int x, int y, int draw)
{
	if (draw)
		my_mlx_pixel_put(data->img, x, y, 0xffb6c1);
	else
		my_mlx_pixel_put(data->img, x, y, 0);
}

void draw_sphere(t_minirt *data)
{
	int	i;
	int j;
	int	len;
	int	high;

	len = data->scene->resolution[0];
	high = data->scene->resolution[1];
	j = -1;
	while (++j < high)
	{
		i = -1;
		while (++i < len)
			draw_pixel(data, i, j, pixel_in_sp(&(data->scene->figs->fig.sp), i, j));
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
	draw_sphere(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (1);
}

