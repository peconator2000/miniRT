#include "miniRT.h"

static void	init_scene(t_scene	*scene)
{
	scene->resolution[0] = 0;
	scene->resolution[1] = 0;
	scene->a_light = 0.0;
	scene->al_color = 0;
	scene->figs = NULL;
}

void	init_mlx(t_minirt *minirt)
{
	int	width;
	int	height;

	minirt->mlx = mlx_init();
	width = minirt->scene->resolution[0];
	height = minirt->scene->resolution[1];
	minirt->win = mlx_new_window(minirt->mlx, width, height, "miniRT");
	minirt->img->img = mlx_new_image(minirt->mlx, width, height);
	minirt->img->addr = mlx_get_data_addr(minirt->img->img, &(minirt->img->bits_per_pixel),
			&(minirt->img->line_length), &(minirt->img->endian));

}

t_minirt	*init()
{
	t_minirt	*minirt;

	minirt = (t_minirt *)err_malloc(sizeof(t_minirt));
	minirt->scene = (t_scene *)err_malloc(sizeof(t_scene));
	minirt->scene->camera = (t_camera *)err_malloc(sizeof(t_camera));
	minirt->scene->light = (t_light *)err_malloc(sizeof(t_light));
	minirt->img = (t_image *)err_malloc(sizeof(t_image));
	init_scene(minirt->scene);
	minirt->scene->camera->degree = 0;
	minirt->scene->light->color = 0;
	minirt->scene->light->brightness = 0.0;
	return (minirt);
}
