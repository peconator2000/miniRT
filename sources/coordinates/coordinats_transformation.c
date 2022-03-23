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
	t_point	reverse_pos;

	wid = scene->resolution[0];
	hig = scene->resolution[1];
	deg_rad = scene->camera->deg * M_PI * pow(180, -1) * 0.5;
	printf("degrad = %f\n", deg_rad);
	scene->camera->view_size[0] = 2 * tan(deg_rad);
	scene->camera->view_size[1] = 2 * tan(deg_rad) * hig * pow(wid, -1);//получаем новые размеры окна просмотра
	vec_equal(&(scene->camera->dir), &(scene->camera->no_vec));//получаем вектор direction
	printf("vector dir = [%f, %f, %f]\n",scene->camera->dir.x, scene->camera->dir.y, scene->camera->dir.z);
	get_vector_rigth(scene->camera);//получаем вектор rigth
	printf("vector rigth = [%f, %f, %f]\n",scene->camera->rigth.x, scene->camera->rigth.y, scene->camera->rigth.z);
	get_vector_up(scene->camera);//получаем вектор up
	printf("vector up = [%f, %f, %f]\n",scene->camera->up.x, scene->camera->up.y, scene->camera->up.z);
	scene->camera->dir.z *= -1;//поворачиваем внутрь экрана
	// vec_mult_num(&(scene->camera->dir), -1);
	vec_equal(&reverse_pos, &(scene->camera->pos));
	vec_mult_num(&reverse_pos, -1);//берем обратные координаты камеры
	new_camera_coords(&(scene->camera->new_pos), reverse_pos, scene->camera);//заполняем координаты камеры в новом базисе
	new_basis_coordinates(&(scene->light->coord), (scene->light->coord), scene->camera);//заполняем координаты света в новом базисе
	printf("new_x = %f new_y = %f new_z = %f\n", scene->camera->new_pos.x, scene->camera->new_pos.y, scene->camera->new_pos.z);
}

void	new_camera_coords(t_point *dot, t_point old, t_camera *cam)//заполняет координатами в новой системе
{
	t_point	up;
	t_point	dir;
	t_point	rig;

	up = cam->up;
	dir = cam->dir;
	rig = cam->rigth;
	printf("rig.x = %f rig.y = %f rig.z  =%f\n", rig.x, rig.y, rig.z);
	printf("up.x = %f up.y = %f up.z  =%f\n", up.x, up.y, up.z);
	printf("dir.x = %f dir.y = %f dir.z  =%f\n", dir.x, dir.y, dir.z);
	(*dot).x = rig.x * old.x + rig.y * old.y + rig.z * old.z;
	(*dot).y = up.x * old.x + up.y * old.y + up.z * old.z;
	(*dot).z = dir.x * old.x + dir.y * old.y + dir.z * old.z;
	printf("ok\n");
}

void	new_basis_coordinates(t_point *dot, t_point old, t_camera *cam)//заполняет координатами в новой системе
{
	t_point	up;
	t_point	dir;
	t_point	rig;
	t_point	c_pos;

	// printf("in cc\n");
	up = cam->up;
	// printf("up\n");
	dir = cam->dir;
	// printf("dir\n");
	rig = cam->rigth;
	// printf("rigth\n");
	c_pos = cam->new_pos;
	// printf("newpos\n");
	(*dot).x = rig.x * old.x + rig.y * old.y + rig.z * old.z - c_pos.x;
	// printf("net old\n");
	(*dot).y = up.x * old.x + up.y * old.y + up.z * old.z - c_pos.y;
	(*dot).z = dir.x * old.x + dir.y * old.y + dir.z * old.z - c_pos.z;
	printf("norm\n");
}

void	get_scene_point(t_point *res, t_scene *scene, double x, double y)
{
	static double	delta_x;
	static double	delta_y;

	if (!delta_x || !delta_y)
	{
		delta_generate(&delta_x, &delta_y, scene);//если они не определены, определяем дельты
		// printf("delta_x = %f delta_y = %f\n", delta_x, delta_y);
	}
	(*res).x = delta_x * x;//scene->camera->view_size[0] + delta_x * x;
	(*res).y = delta_y * y;//scene->camera->view_size[1] - delta_y * y;
	(*res).z = -1;
}
