#include "miniRT.h"

void get_tmp_vec(t_point *tmp, t_point dir)
{
	if (dir.x == 0 && dir.z == 0) // значит коллинеарны с tmp1
		vec_fill(tmp, -1, 0, 0);
	else
		vec_fill(tmp, 0, 1, 0);
}

void	get_vector_rigth(t_camera *cam)
{
	t_point	tmp;

	get_tmp_vec(&tmp, cam->dir);//получили пробный вектор
	vec_mult_vec(&(cam->rigth), cam->dir, tmp);//векторное умножение
	normalize2(&(cam->rigth), (cam->rigth));
}

void	get_vector_up(t_camera *cam)
{
	vec_mult_vec(&(cam->up), cam->rigth, cam->dir);
	normalize2(&(cam->up), (cam->up));
}

void	get_new_basis(t_scene *scene)
{
	double	wid;
	double	hig;
	double	deg_rad;

	wid = scene->resolution[0];
	hig = scene->resolution[1];
	deg_rad = scene->camera->deg * M_PI * pow(180, -1) * 0.5;
	scene->camera->view_size[0] = 2 * tan(deg_rad);
	scene->camera->view_size[1] = 2 * tan(deg_rad) * hig * pow(wid, -1);//получаем новые размеры окна просмотра
	vec_equal(&(scene->camera->dir), &(scene->camera->no_vec));//получаем вектор direction
	get_vector_rigth(scene->camera);//получаем вектор rigth
	get_vector_up(scene->camera);//получаем вектор up
	// vec_mult_num(&(scene->camera->dir), -1);//поворачиваем внутрь экрана
	camera_diff(&(scene->light->coord), scene->camera);
	//print
	printf("vector dir = [%f, %f, %f]\n",scene->camera->dir.x, scene->camera->dir.y, scene->camera->dir.z);
	printf("vector rigth = [%f, %f, %f]\n",scene->camera->rigth.x, scene->camera->rigth.y, scene->camera->rigth.z);
	printf("vector up = [%f, %f, %f]\n",scene->camera->up.x, scene->camera->up.y, scene->camera->up.z);
}

t_point lookat_cam(t_point pos, t_point rig, t_point up, t_point dir)
{
	t_point res;

	res.x = (pos.x * rig.x + pos.y * rig.y + pos.z * rig.z);// * (-1);
	res.y = (pos.x * up.x + pos.y * up.y + pos.z * up.z);// * (-1);
	res.z = (pos.x * dir.x + pos.y * dir.y + pos.z * dir.z);// * (-1);
	return (res);
}

void	new_basis_coordinates(t_point *dot, t_point old, t_camera *cam)//lookat matrix
{
	t_point	up;
	t_point	dir;
	t_point	rig;
	t_point	c_pos;

	up = cam->up;
	dir = cam->dir;
	rig = cam->rigth;
	c_pos = lookat_cam(cam->pos, rig, up, dir);
	(*dot).x = rig.x * old.x + rig.y * old.y + rig.z * old.z + c_pos.x - cam->pos.x;
	(*dot).y = up.x * old.x + up.y * old.y + up.z * old.z + c_pos.y - cam->pos.y;
	(*dot).z = dir.x * old.x + dir.y * old.y + dir.z * old.z + c_pos.z - cam->pos.z;
}

void	get_scene_point(t_point *res, t_scene *scene, double x, double y)//, double z)
{
	static double	delta_x;
	static double	delta_y;

	if (!delta_x || !delta_y)
		delta_generate(&delta_x, &delta_y, scene);
	// printf("delta = %f deltay = %f\n", delta_x, delta_y);
	(*res).x = delta_x * x;//scene->camera->view_size[0] + delta_x * x;
	(*res).y = delta_y * y;//scene->camera->view_size[1] - delta_y * y;
	(*res).z = 1;
	// (*res).z = delta_x * z;
}
