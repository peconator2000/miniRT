#include "miniRT.h"

void	get_scr_vec(t_point *ray, t_camera *cam, t_point dot)
{
	// (void)cam;
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


t_point	get_sp_dot(t_point m, double min_t, t_scene *sc)
{
	t_point res;

	// (void)sc;
	res.x =  m.x * (min_t) - sc->camera->pos.x;
	res.y = m.y * (min_t) - sc->camera->pos.y;
	res.z =  m.z * (min_t) - sc->camera->pos.z;
	return (res);
}

double get_min_param(double discr, t_point m, t_point ray, t_scene *sc)
{
	double	root1;
	double	root2;
	t_point	sca1;
	t_point	sca2;
	double	dd = -3;

	root1 = 2 * m.x * ray.x + 2 * m.y * ray.y + 2 * m.z * ray.z * (-1) + sqrt(discr);
	root1 *= pow(2 * (pow(m.x, 2) + pow(m.y , 2) + pow(m.z, 2)), -1);
	root2 = 2 * m.x * ray.x + 2 * m.y * ray.y + 2 * m.z * ray.z * (-1) - sqrt(discr);
	root2 *= pow(2 * (pow(m.x, 2) + pow(m.y , 2) + pow(m.z, 2)), -1);
	sca1 = get_sp_dot(m, root1, sc);
	sca2 = get_sp_dot(m, root2, sc);
	// printf("t_1 = %f\n", root1);
	// printf("t_2 = %f\n", root2);
	if (root1 >= dd || root2 >= dd)
	{
		if (root1 >= dd && root2 >= dd)
		{
			if (root1 < root2)
				return (root1);
			return (root2);
		}
		if (root1 >= dd)
			return (root1);
		return (root2);
	}
	if (root1 < root2)
		return (root1);
	else
		return (root2);
}

void	is_sphere(t_scene *sc, t_point p, t_color *min_color, double *min_t, t_figures *sp)
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	t_min = -1;
	double	discr;
	t_point	sp_dot;
	t_point	op;//вектор направления
	t_point	o = sc->camera->pos;//позиция камеры
	t_point	s = sp->fig.sp.coord;//центр сферы
	double	rad = sp->fig.sp.diameter * 0.5;//радиус

	op.x = p.x - o.x;
	op.y = p.y - o.y;
	op.z = p.z - o.z;
	a = op.x * op.x + op.y * op.y + op.z * op.z;
	b = 2 * (op.x * (o.x - s.x) + op.y * (o.y - s.y) + op.z * (o.z - s.z));
	c = ((o.x - s.x) * (o.x - s.x) + (o.y - s.y) * (o.y - s.y) + (o.z - s.z) * (o.z - s.z) - rad * rad);
	discr = b * b - 4 * a * c;
	t1 = (b * (-1) + sqrt(discr)) / (2 * a);
	t2 = (b * (-1) - sqrt(discr)) / (2 * a);
	// if (t1 >= 1 || t2 >= 1)
	// {
	// 	if (t1 >= 1 && t2 >= 1)
	// 	{
	// 		if (t1 < t2)
	// 			t_min = t1;
	// 		else
	// 			t_min = t2;
	// 	}
	// 	else
	// 	{
	// 		if (t1 >= 1)
	// 			t_min = t1;
	// 		else	
	// 			t_min = t2;
	// 	}
	// }
	// else
	// 	return ;
	sp_dot.x = op.x * t_min + o.x;
	sp_dot.y = op.y * t_min + o.y;
	sp_dot.z = op.z * t_min + o.z;
	if (*min_t == -1 || t_min < *min_t)
	{
		*min_t = t_min;
		*min_color = sp->color;
		// *min_color = get_ligth_sphere(sp, sp_dot, *min_color, sc->light);
	}	
}

double	get_pl_numerator(t_point cam, t_point norm, t_point N)
{
	double	res;

	res = norm.x * N.x + norm.y * N.y + norm.z * N.z;
	res = res - norm.x * cam.x - norm.y * cam.y - norm.z * cam.z;
	return (res);
}

double	get_pl_denominator(t_point m, t_point norm)
{
	double	res;

	res = norm.x * m.x + norm.y * m.y + norm.z * m.z;
	return (res);
}

void	is_plane(t_scene *sc, t_point dot, t_color *min_color, double *min_t, t_figures *pl)
{
	t_point	m;//вектор направления
	double	num;//числитель
	double	den;//знаменатель
	double	cur_t;

	get_scr_vec(&m, sc->camera, dot);//пускаем луч
	num = get_pl_numerator(sc->camera->pos, pl->no_vec, pl->fig.pl.coord);
	den = get_pl_denominator(m, pl->no_vec);
	if (num == 0 && den == 0)
		return ;//ничего не делаем
	else
	{                                                                                                                                                                                              
		cur_t = num * pow(den, -1);
		if (cur_t < 1)
			return ;
		if (*min_t == -1 || cur_t < *min_t)//fabs(cur_t) < fabs(*min_t)
		{
			*min_t= cur_t;
			*min_color = pl->color;
			// *min_color = get_ligth_plane(pl, get_sp_dot(m, *min_t, sc), *min_color, sc->light);
		}
	}
}
