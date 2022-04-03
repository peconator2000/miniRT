#include "miniRT.h"

void get_new_cylinder_basis(t_figures *fig, t_point *r, t_point *u, t_point *d)
{
	t_point tmp;

	vec_fill(d, fig->no_vec.x, fig->no_vec.y, fig->no_vec.z);//заполняем z'
	vec_fill(&tmp, 0, 1, 0);//заполняем tmp
	if ((*d).y == 1 || (*d).y == -1)
	{
		if ((*d).y == 1)
			vec_fill(r, 1, 0, 0);
		else
			vec_fill(r, -1, 0, 0);
	}
	else
		vec_mult_vec(r, tmp, *d);
	vec_mult_vec(u, *d, *r);
	normalize2(r, *r);
	normalize2(u, *u);
	normalize2(d, *d);
}

double get_matrix_determinant(t_point r, t_point u, t_point d)
{
	double	res;

	res = r.x * (u.y * d.z - u.z * d.y);
	res -= r.y * (u.x * d.z - d.x * u.z);
	res += r.z * (u.x * d.y - d.x * u.y);
	return (res);
}

void get_cy_basis_dot(t_point dot, t_point *new, t_point r, t_point u, t_point d, t_point k)//сюда посылается точка в мировых координатах, а мы переводим ее в новые связанные с цилиндром
{
	double det;//определитель целой матрицы
	t_point r_new;
	t_point u_new;
	t_point d_new;

	det = get_matrix_determinant(r, u, d);
	r_new.x = u.y * d.z - d.y * u.z;
	r_new.y = (-1) * (u.x * d.z - d.x * u.z);
	r_new.z = u.x * d.y - d.x * u.y;

	u_new.x = (-1) * (r.y * d.z - d.y * r.z);
	u_new.y = r.x * d.z - d.x * r.z;
	u_new.z = (-1) * (r.x * d.y - d.x * r.y);

	d_new.x = r.y * u.z - u.y * r.z;
	d_new.y = (-1) * (r.x * u.z - u.x * r.z);
	d_new.z = r.x * u.y - u.x * r.y;

	(*new).x = (r_new.x * (dot.x - k.x) + u_new.x * (dot.y - k.y) + d_new.x * (dot.z - k.z)) / det;
	(*new).y = (r_new.y * (dot.x - k.x) + u_new.y * (dot.y - k.y) + d_new.y * (dot.z - k.z)) / det;
	(*new).z = (r_new.z * (dot.x - k.x) + u_new.z * (dot.y - k.y) + d_new.z * (dot.z - k.z)) / det;
}

void is_cylinder(t_scene *sc, t_point p, t_color *min_color, double *min_t, t_figures *cy)
{
	//для нового базиса относительно цилиндра
	t_point r;//новый вектор x' относительно осей цилиндра
	t_point u;//y'
	t_point d;//z'

	t_point o = sc->camera->pos;
	//для новых координат камеры и точки на экране просмотра
	t_point new_o;//координата камеры в системе цилиндра
	t_point new_p;//координата камеры в системе цилиндра
	t_point new_op;//новое направление в системе цилиндра
	t_point k = cy->fig.cy.coord;//координата центра цилиндра

	//квадратное уравнение
	double discr;
	double a;
	double b;
	double c;
	double rad = cy->fig.cy.diameter * (0.5);

	double t1;
	double t2;
	double t_min = -1;
	double t_min2 = -1;
	t_point cy_dot;
	t_point norm;
	double hei = cy->fig.cy.height;

	get_new_cylinder_basis(cy, &r, &u, &d);
	cy->r = r;
	cy->u = u;
	cy->d = d;
	get_cy_basis_dot(p, &new_p, r, u, d, k);
	get_cy_basis_dot(o, &new_o, r, u, d, k);

	new_op.x = new_p.x - new_o.x;
	new_op.y = new_p.y - new_o.y;
	new_op.z = new_p.z - new_o.z;
	// normalize2(&new_op, new_op);

	a = new_op.x * new_op.x + new_op.y * new_op.y;
	b = 2 * new_op.x * new_o.x + 2 * new_op.y * new_o.y;
	c = new_o.x * new_o.x + new_o.y * new_o.y - rad * rad;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	if (a < 0.00001)// цилиндр повернут
	{

		if (new_op.x == 0 && new_op.y == 0 && new_op.z > 0)
			cy_dot.z = (new_op.z + new_o.z) * hei * (-0.5);
		else
			cy_dot.z = (new_op.z + new_o.z) * hei * (0.5);
		cy_dot.x = new_o.x;
		cy_dot.y = new_o.y;
		// printf("hey\n");
		if (cy_dot.x * cy_dot.x + cy_dot.y * cy_dot.y - rad * rad > 0.00001)
			return ;
		vec_fill(&norm, 0, 0, cy_dot.z);
		normalize2(&norm, norm);
	}
	else
	{
		t1 = ((-1) * b + sqrt(discr)) / (2 * a);
		t2 = ((-1) * b - sqrt(discr)) / (2 * a);
		if (t1 >= 1 || t2 >= 1)
		{
			if (t1 >= 1 && t2 >= 1)
			{
				if (t1 < t2)
				{
					t_min = t1;
					t_min2 = t2;
				}
				else
				{
					t_min = t2;
					t_min2 = t1;
				}
			}
			else
			{
				if (t1 >= 1)
				{
					t_min = t1;
					t_min2 = t2;
				}
				else
				{
					t_min = t2;
					t_min2 = t1;
				}
			}
		}
		else
			return ;

		cy_dot.x = new_op.x * t_min + new_o.x;
		cy_dot.y = new_op.y * t_min + new_o.y;
		cy_dot.z = new_op.z * t_min + new_o.z;

		if (cy_dot.z < (-0.5) * hei || cy_dot.z > hei * (0.5))
			t_min = t_min2;

		cy_dot.x = new_op.x * t_min + new_o.x;
		cy_dot.y = new_op.y * t_min + new_o.y;
		cy_dot.z = new_op.z * t_min + new_o.z;
		if (cy_dot.z < (-0.5) * hei || cy_dot.z > hei * (0.5))
			return ;
		vec_fill(&norm, cy_dot.x, cy_dot.y, 0);
		normalize2(&norm, norm);
		*min_t = t_min;
		*min_color = cy->color;
	}
	// if (*min_t == -1 || t_min < *min_t)
	// {

		*min_t = t_min;
		// printf("ok\n");
		*min_color = cy->color;
		// fill_color(min_color, 255, 0, 0);
		*min_color = get_ligth_cylinder(cy, cy_dot, norm, *min_color, sc->light);
	// }			
}
