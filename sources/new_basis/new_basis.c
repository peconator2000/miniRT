#include "miniRT.h"

void	get_norm(t_point *dot)
{
	double	len;

	len = pow((*dot).x, 2) + pow((*dot).y, 2) + pow((*dot).z, 2);
	(*dot).x = (*dot).x * pow (len,-1);
	(*dot).y = (*dot).y * pow(len, -1);
	(*dot).z = (*dot).z * pow(len, -1);
}

void	get_d(t_camera *cam)
{
	// get_norm(&(cam->no_vec));
	vec_fill(&(cam->dir), cam->no_vec.x, cam->no_vec.y, cam->no_vec.z);
}

void	get_u(t_camera *cam)
{
	t_point tmp;

	if (cam->dir.x == 0 && cam->dir.z == 0)
		vec_fill(&tmp, 0, 1, 0);
	else
		vec_fill(&tmp, 1, 0, 0);
	vec_mult_vec(&(cam->up), cam->dir, tmp);
}

void	get_r(t_camera *cam)
{
	vec_mult_vec(&(cam->rigth), cam->up, cam->dir);
}

void new_basis(t_scene *scene)
{
	get_d(scene->camera);
	get_u(scene->camera);
	get_r(scene->camera);
	get_norm(&(scene->camera->dir));
	get_norm(&(scene->camera->up));
	get_norm(&(scene->camera->dir));
}