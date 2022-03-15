#include "miniRT.h"

void	parse_resolution(t_minirt *minirt, char **str)
{
	skip_space(str);
	minirt->scene->resolution[0] = str_to_int(str);
	check_range(minirt->scene->resolution[0], 1, INFINITY, "RESOLUTION");
	minirt->scene->resolution[1] = str_to_int(str);
	check_range(minirt->scene->resolution[1], 1, INFINITY, "RESOLUTION");
	init_mlx(minirt);
}

void	parse_ambient_light(t_minirt *minirt, char **str)
{
	skip_space(str);
	minirt->scene->a_light = str_to_double(str);
	check_range(minirt->scene->a_light, 0.0, 1.0, "AMBIENT LIGHT");
	skip_space(str);
	minirt->scene->al_color =  parse_color(str);
}

void	parse_light(t_minirt *minirt, char **str)
{
	(void)minirt;
	(void)str;
}

void	parse_camera(t_minirt *minirt, char **str)
{
	(void)minirt;
	(void)str;
}
