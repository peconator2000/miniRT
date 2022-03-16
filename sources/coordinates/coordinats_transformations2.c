#include "miniRT.h"

void delta_generate(double *delta_x, double *delta_y, t_scene *scene)
{
	(*delta_x) = scene->camera->view_size[0] * pow(scene->resolution[0], -1);
	(*delta_y) = scene->camera->view_size[1] * pow(scene->resolution[1], -1);
}