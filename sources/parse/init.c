#include "miniRT.h"

t_minirt	*init()
{
	t_minirt	*minirt;

	minirt = (t_minirt *)err_malloc(sizeof(t_minirt));
	// init_mlx(minirt);
	// minirt = init_scene();
	// minirt->scene->camera = init_camera();
	// minirt->scene->light = init_light;
	return (minirt);
}
