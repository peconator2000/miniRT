#include "miniRT.h"

static void	init_scene(t_scene	*scene)
{
	scene->resolution[0] = 0;
	scene->resolution[1] = 0;
	scene->a_light = 0.0;
	scene->al_color = create_color(0, 0, 0);
	scene->figs = NULL;
}

void init_camera(t_camera *cam)//test version
{
	cam->view_size[0] = 0;//
	cam->view_size[1] = 0;//
	cam->deg = 90;//
	// vec_fill(&(cam->pos), 0, 0, 0);
	// vec_fill(&(cam->no_vec), 0, 0, 0);
	// vec_fill(&(cam->new_pos), 0, 0, 0);
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

void	create_image(t_minirt *data)
{
	t_image	*img;
	int len;
	int high;

	img = malloc(sizeof(t_image));
	len = data->scene->resolution[0];
	high = data->scene->resolution[1];
	if (!img)
		exit(0);
	img->img = mlx_new_image(data->mlx, len,high) ;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	data->img = img;
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
	// init_camera(minirt->scene->camera);
	minirt->scene->camera->deg = 0;
	minirt->scene->light->color.r = 255;
	minirt->scene->light->color.g = 255;
	minirt->scene->light->color.b = 255;
	minirt->scene->light->brightness = 0.0;
	return (minirt);
}
