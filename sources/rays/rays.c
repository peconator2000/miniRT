#include "miniRT.h"

void	get_scr_vec(t_point *ray, t_camera *cam, t_point dot)
{
	(*ray).x = dot.x - cam->pos.x;
	(*ray).y = dot.y - cam->pos.y;
	(*ray).z = dot.z - cam->pos.z;
}

void	get_discr(double *discr, t_point m, t_point ray, double rad)
{
	double	a;
	double	b;
	double	c;

	a = pow(m.x, 2) + pow(m.y , 2) + pow(m.z, 2);
	b = 2 * m.x * ray.x + 2 * m.y * ray.y + 2 * m.z * ray.z;
	c = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2) - pow(rad, 2);
	(*discr) = (b * b) - (4 * a * c);
}

double get_min_param(double discr, t_point m, t_point ray)
{
	double	root1;
	double	root2;

	root1 = vec_scalar_mult(m, ray) * (-1) + sqrt(discr);
	root1 *= pow(2 * (pow(m.x, 2) + pow(m.y, 2) + pow(m.z, 2)), -1);
	root2 = vec_scalar_mult(m, ray) * (-1) - sqrt(discr);
	root2 *= pow(2 * (pow(m.x, 2) + pow(m.y, 2) + pow(m.z, 2)), -1);
	if (root1 > 1 || root2 > 1)
	{
		if (root1 > 1 && root2 > 1)
		{
			if (root1 < root2)
				return (root1);
			return (root2);
		}
		if (root1 > 1)
			return (root1);
		return (root2);
	}
	return (-1);
}

t_point	get_sp_dot(t_point m, t_scene *sc, double min_t)
{
	t_point res;

	res.x = m.x * min_t + sc->camera->pos.x;
	res.y = m.y * min_t + sc->camera->pos.y;
	res.z = m.z * min_t + sc->camera->pos.z;
	return (res);
}

void	is_sphere(t_scene *sc, t_point dot, t_color *min_color, double *min_t, t_figures *sp)
{
	t_point	m;//вектор направления
	t_point	ray;//вектор cam - cen
	double	cur_t;
	double	discr;

	get_scr_vec(&m, sc->camera, dot);
	ray.x = sc->camera->pos.x - sp->fig.sp.coord.x;
	ray.y = sc->camera->pos.y - sp->fig.sp.coord.y;
	ray.z = sc->camera->pos.z - sp->fig.sp.coord.z;
	get_discr(&discr, m, ray, sp->fig.sp.diameter * 0.5);
	if (discr < 0)
		return ;
	cur_t = get_min_param(discr, m, ray);
	if ((*min_t == -1 || cur_t < *min_t) && cur_t > 1)
	{
		*min_t = cur_t;
		*min_color = sp->color;
		*min_color = get_ligth_sphere(sp, get_sp_dot(m, sc, *min_t), *min_color, sc->light);
	}
}