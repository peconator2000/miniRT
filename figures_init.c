#include "minirt.h"

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

t_screen	*screen_init(void)
{
	t_screen	*scr;
	int			len;
	int			high;

	len = 800;
	high = 1200;
	scr = malloc(sizeof(t_screen));
	scr->len = len;
	scr->high = high;
	scr->init = mlx_init();
	scr->win = mlx_new_window(scr->init, len, high, "miniRT");
	create_image(scr);
	return (scr);
}

t_sphere	*sphere_init(void)
{
	t_sphere	*sph;

	sph = malloc(sizeof(t_sphere));
	if (!sph)
		return (NULL);
	sph->rad = 100;
	sph->centre.x = 400;
	sph->centre.y = 600;
	sph->centre.z = 0;
	return (sph);
}

t_data	*data_init(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->scr = screen_init();
	data->sph = sphere_init();
	if (!data->scr || !data->sph)
		return (0);
	return (data);
}
