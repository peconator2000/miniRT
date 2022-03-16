#include "miniRT.h"

void get_tmp_vec(t_point *tmp, t_point dir)
{
	if (dir.x == 0 && dir.z == 0)//значит коллинеарны с tmp1
		vec_fill(tmp, -1, 0, 0);
	else
		vec_fill(tmp, 0, 1, 0);
}

void	get_vector_rigth(t_camera *cam)
{
	t_point	dir;
	t_point	tmp;

	get_tmp_vec(&tmp, cam->dir);//получили пробный вектор
	vec_mult_vec(&(cam->rigth), cam->dir, tmp);//векторное умножение
}

void	get_vector_up(t_camera *cam)
{
	vec_mult_vec(&(cam->up), cam->dir, cam->rigth);
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
	scene->camera->view_size[0] = 2 * tan(deg_rad);
	scene->camera->view_size[1] = 2 * tan(deg_rad) * hig * pow(wid, -1);//получаем новые рзамеры окна просмотра
	vec_equal(&(scene->camera->dir), &(scene->camera->no_vec));//получаем вектор direction
	get_vector_rigth(scene->camera);//получаем вектор rigth
	get_vector_up(scene->camera);//получаем вектор up
	scene->camera->dir.z *= -1;//поворачиваем внутрь экрана
	vec_mult_num(&reverse_pos, -1);//берем обратные координаты камеры
	new_basis_coordinates(&(scene->camera->new_pos), reverse_pos, scene->camera);//заполняем координаты камеры в новом базисе
}

void	new_basis_coordinates(t_point *dot, t_point old, t_camera *cam)//заполняет координатами в новой системе
{
	t_point	up;
	t_point	dir;
	t_point	rig;
	t_point	c_pos;

	up = cam->up;
	dir = cam->dir;
	rig = cam->rigth;
	c_pos = cam->new_pos;
	(*dot).x = rig.x * old.x + rig.y * old.y + rig.z * old.z - c_pos.x;
	(*dot).y = up.x * old.x + up.y * old.y + up.z * old.z - c_pos.y;
	(*dot).z = dir.x * old.x + dir.y * old.y + dir.z * old.z - c_pos.z;
}

void	get_scene_point(t_point *res, t_scene *scene, int x, int y)
{
	static double	delta_x;
	static double	delta_y;

	if (!delta_x || !delta_y)
		delta_generate(&delta_x, &delta_y, scene);//если они не определены, определяем дельты
	(*res).x = scene->camera->view_size[0] + delta_x * x;
	(*res).y = scene->camera->view_size[1] - delta_y * y;
	(*res).z = 1;
}
