#include "minirt.h"

double eps = 0.000001;

int pixel_in_sp(t_sphere *sp, int x, int y)
{
	double new_x;
	double new_y;
	double new_rad;

	new_x = x - sp->centre.x;
	new_y = y - sp->centre.y;
	new_rad = sqrt(new_x * new_x + new_y * new_y);
	if (new_rad - sp->rad < eps)
		return (1);
	return (0);
}

void	create_image(t_screen *scr)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		exit(0);
	img->img = mlx_new_image(scr->init, scr->len, scr->high);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	scr->img = img;
}

void draw_pixel(t_data *data, int x, int y, int draw)
{
	if (draw)
		my_mlx_pixel_put(data->scr->img, x, y, 0xffb6c1);
	else
		my_mlx_pixel_put(data->scr->img, x, y, 0x6cb9dd9);
}

void draw_sphere(t_data *data)
{
	int	i;
	int j;
	int	len;
	int	high;

	len = data->scr->len;
	high = data->scr->high;
	j = -1;
	while (++j < high)
	{
		i = -1;
		while (++i < len)
			draw_pixel(data, i, j, pixel_in_sp(data->sph, i, j));
	}
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	draw_figures(t_data *data)
{
	t_screen *scr;

	scr = data->scr;
	draw_sphere(data);
	mlx_put_image_to_window(scr->init, scr->win, scr->img->img, 0, 0);
	return (1);
}

