#include "miniRT.h"

void show_vec(char *str, t_point vec)
{
	printf("%s (%f, %f, %f)\n", str, vec.x, vec.y, vec.z);
}

void get_new_cylinder_basis(t_figures *cy)
{
	t_point tmp;

	vec_fill(&(cy->d), cy->no_vec.x, cy->no_vec.y, cy->no_vec.z);
	vec_fill(&tmp, 0, 1, 0);
	if ((cy->d).y == 1 || (cy->d).y == -1)
	{
		if ((cy->d).y == 1)
			vec_fill(&(cy->r), 1, 0, 0);
		else
			vec_fill(&(cy->r), -1, 0, 0);
	}
	else
		vec_mult_vec(&(cy->r), tmp, (cy->d));
	vec_mult_vec(&(cy->u), cy->d, cy->r);
	normalize2(&(cy->r), (cy->r));
	normalize2(&(cy->u), (cy->u));
	normalize2(&(cy->d), (cy->d));
}

double get_matrix_determinant(t_point r, t_point u, t_point d)
{
	double	res;

	res = r.x * (u.y * d.z - u.z * d.y);
	res -= r.y * (u.x * d.z - d.x * u.z);
	res += r.z * (u.x * d.y - d.x * u.y);
	return (res);
}

void get_cy_basis_dot(t_point dot, t_point *new, t_figures *fig, t_point k)//сюда посылается точка в мировых координатах, а мы переводим ее в новые связанные с цилиндром
{
	double det;//определитель целой матрицы
	t_point r_new;
	t_point u_new;
	t_point d_new;

	det = get_matrix_determinant(fig->r, fig->u, fig->d);
	r_new.x = fig->u.y * fig->d.z - fig->d.y * fig->u.z;
	r_new.y = (-1) * (fig->u.x * fig->d.z - fig->d.x * fig->u.z);
	r_new.z = fig->u.x * fig->d.y - fig->d.x * fig->u.y;

	u_new.x = (-1) * (fig->r.y * fig->d.z - fig->d.y * fig->r.z);
	u_new.y = fig->r.x * fig->d.z - fig->d.x * fig->r.z;
	u_new.z = (-1) * (fig->r.x * fig->d.y - fig->d.x * fig->r.y);

	d_new.x = fig->r.y * fig->u.z - fig->u.y * fig->r.z;
	d_new.y = (-1) * (fig->r.x * fig->u.z - fig->u.x * fig->r.z);
	d_new.z = fig->r.x * fig->u.y - fig->u.x * fig->r.y;

	(*new).x = (r_new.x * (dot.x - k.x) + u_new.x * (dot.y - k.y) + d_new.x * (dot.z - k.z)) / det;
	(*new).y = (r_new.y * (dot.x - k.x) + u_new.y * (dot.y - k.y) + d_new.y * (dot.z - k.z)) / det;
	(*new).z = (r_new.z * (dot.x - k.x) + u_new.z * (dot.y - k.y) + d_new.z * (dot.z - k.z)) / det;
}

void swap_t(t_equ *equ)
{
	double	mid;

	if ((*equ).t2 < (*equ).t1)
	{
		mid = (*equ).t1;
		(*equ).t1 = (*equ).t2;
		(*equ).t2 = mid;
	}
}

int rem_cylinder(t_ray ray, double t_min, double hei)
{
	t_point cy_dot;

	get_ray_dot(&cy_dot, ray, t_min);
	if (cy_dot.z - (-0.5) * hei < 0.0001 || cy_dot.z - hei * (0.5) < 0.0001)
		return (0);
	return (1);
}

int is_valid_cy_param(t_equ *equ)
{
	double t1 = equ->t1;
	double t2 = equ->t2;
	double t_min;

	if (t1 >= 1 || t2 >= 1)
	{
		if (t1 >= 1 && t2 >= 1)
		{
			if (t1 < t2)
				t_min = t1;
			else
				t_min = t2;
		}
		else
		{
			if (t1 >= 1)
				t_min = t1;
			else
				t_min = t2;
		}
	}
	else
		return (0);
	equ->t_min = t_min;
	return (1);
}

double	get_cy_t(t_equ equ, double hei, t_ray new_ray)
{
	double t_min;


	equ.t1 = ((-1) * equ.b + sqrt(equ.discr)) / (2 * equ.a);
	equ.t2 = ((-1) * equ.b - sqrt(equ.discr)) / (2 * equ.a);
	swap_t(&equ);
	// printf("t1 = %f\n", equ.t1);
	// printf("t2 = %f\n", equ.t2);
	if (!is_valid_cy_param(&equ))
		return (-1);
	t_min = equ.t_min;
	if (rem_cylinder(new_ray, t_min, hei))
	{
		t_min = equ.t2;
	}
	if (rem_cylinder(new_ray, t_min, hei))
		return (-1);
	return (t_min);
}

double is_cylinder(t_point o, t_point p, t_figures *cy)
{
	t_ray	new_ray;
	t_equ	equ;
	double	rad;
	double	hei;
	t_point	k;

	k = cy->fig.cy.coord;
	hei = cy->fig.cy.height;
	rad = cy->fig.cy.diameter * (0.5);
	get_new_cylinder_basis(cy);
	get_cy_basis_dot(p, &(new_ray.p), cy, k);
	get_cy_basis_dot(o, &(new_ray.o), cy, k);
	ray_fill(&new_ray, new_ray.o, new_ray.p);
	equ.a = new_ray.op.x * new_ray.op.x + new_ray.op.y * new_ray.op.y;
	equ.b = 2 * new_ray.op.x * new_ray.o.x + 2 * new_ray.op.y * new_ray.o.y;
	equ.c = new_ray.o.x * new_ray.o.x + new_ray.o.y * new_ray.o.y - rad * rad;
	equ.discr = equ.b * equ.b - 4 * equ.a * equ.c;
	// printf("(a, b, c, discr) = (%f, %f, %f, %f)\n", equ.a, equ.b, equ.c, equ.discr);
	if (equ.discr < 0)
		return (-1);
	if (fabs(equ.a) < 0.00001)// крышка
		return (-1);
	return (get_cy_t(equ, hei, new_ray));		
}



























// void get_new_cylinder_basis(t_figures *fig, t_point *r, t_point *u, t_point *d)
// {
// 	t_point tmp;

// 	vec_fill(d, fig->no_vec.x, fig->no_vec.y, fig->no_vec.z);//заполняем z'
// 	vec_fill(&tmp, 0, 1, 0);//заполняем tmp
// 	if ((*d).y == 1 || (*d).y == -1)
// 	{
// 		if ((*d).y == 1)
// 			vec_fill(r, 1, 0, 0);
// 		else
// 			vec_fill(r, -1, 0, 0);
// 	}
// 	else
// 		vec_mult_vec(r, tmp, *d);
// 	vec_mult_vec(u, *d, *r);
// 	normalize2(r, *r);
// 	normalize2(u, *u);
// 	normalize2(d, *d);
// }

// double get_matrix_determinant(t_point r, t_point u, t_point d)
// {
// 	double	res;

// 	res = r.x * (u.y * d.z - u.z * d.y);
// 	res -= r.y * (u.x * d.z - d.x * u.z);
// 	res += r.z * (u.x * d.y - d.x * u.y);
// 	return (res);
// }

// void get_cy_basis_dot(t_point dot, t_point *new, t_point r, t_point u, t_point d, t_point k)//сюда посылается точка в мировых координатах, а мы переводим ее в новые связанные с цилиндром
// {
// 	double det;//определитель целой матрицы
// 	t_point r_new;
// 	t_point u_new;
// 	t_point d_new;

// 	det = get_matrix_determinant(r, u, d);
// 	r_new.x = u.y * d.z - d.y * u.z;
// 	r_new.y = (-1) * (u.x * d.z - d.x * u.z);
// 	r_new.z = u.x * d.y - d.x * u.y;

// 	u_new.x = (-1) * (r.y * d.z - d.y * r.z);
// 	u_new.y = r.x * d.z - d.x * r.z;
// 	u_new.z = (-1) * (r.x * d.y - d.x * r.y);

// 	d_new.x = r.y * u.z - u.y * r.z;
// 	d_new.y = (-1) * (r.x * u.z - u.x * r.z);
// 	d_new.z = r.x * u.y - u.x * r.y;

// 	(*new).x = (r_new.x * (dot.x - k.x) + u_new.x * (dot.y - k.y) + d_new.x * (dot.z - k.z)) / det;
// 	(*new).y = (r_new.y * (dot.x - k.x) + u_new.y * (dot.y - k.y) + d_new.y * (dot.z - k.z)) / det;
// 	(*new).z = (r_new.z * (dot.x - k.x) + u_new.z * (dot.y - k.y) + d_new.z * (dot.z - k.z)) / det;
// }

// void is_cylinder(t_scene *sc, t_point p, t_color *min_color, double *min_t, t_figures *cy)
// {
// 	//для нового базиса относительно цилиндра
// 	t_point r;//новый вектор x' относительно осей цилиндра
// 	t_point u;//y'
// 	t_point d;//z'

// 	t_point o = sc->camera->pos;
// 	//для новых координат камеры и точки на экране просмотра
// 	t_point new_o;//координата камеры в системе цилиндра
// 	t_point new_p;//координата камеры в системе цилиндра
// 	t_point new_op;//новое направление в системе цилиндра
// 	t_point k = cy->fig.cy.coord;//координата центра цилиндра

// 	//квадратное уравнение
// 	double discr;
// 	double a;
// 	double b;
// 	double c;
// 	double rad = cy->fig.cy.diameter * (0.5);

// 	double t1;
// 	double t2;
// 	double t_min = -1;
// 	double t_min2 = -1;
// 	t_point cy_dot;
// 	t_point norm;
// 	double hei = cy->fig.cy.height;

// 	get_new_cylinder_basis(cy, &r, &u, &d);
// 	cy->r = r;
// 	cy->u = u;
// 	cy->d = d;
// 	get_cy_basis_dot(p, &new_p, r, u, d, k);
// 	get_cy_basis_dot(o, &new_o, r, u, d, k);

// 	new_op.x = new_p.x - new_o.x;
// 	new_op.y = new_p.y - new_o.y;
// 	new_op.z = new_p.z - new_o.z;
// 	// normalize2(&new_op, new_op);

// 	a = new_op.x * new_op.x + new_op.y * new_op.y;
// 	b = 2 * new_op.x * new_o.x + 2 * new_op.y * new_o.y;
// 	c = new_o.x * new_o.x + new_o.y * new_o.y - rad * rad;
// 	discr = b * b - 4 * a * c;
// 	printf("(a, b, c, discr) = (%f, %f, %f, %f)\n", a, b, c, discr);
// 	if (discr < 0)
// 		return ;
// 	if (fabs(a) < 0.00001)// цилиндр повернут
// 	{

// 		if (new_op.x == 0 && new_op.y == 0 && new_op.z > 0)
// 			cy_dot.z = (new_op.z + new_o.z) * hei * (-0.5);
// 		else
// 			cy_dot.z = (new_op.z + new_o.z) * hei * (0.5);
// 		cy_dot.x = new_o.x;
// 		cy_dot.y = new_o.y;
// 		// printf("hey\n");
// 		if (new_o.x * new_o.x + new_o.y * new_o.y - rad * rad > 0.00001)
// 			return ;
// 		// printf("i am here\n");
// 		vec_fill(&norm, 0, 0, cy_dot.z);
// 		normalize2(&norm, norm);
// 		// printf("dot = (%f, %f, %f) norm = (%f, %f, %f)\n", new_o.x, new_o.y, new_o.z, norm.x, norm.y, norm.z);
// 		return ;
// 	}
// 	else
// 	{
// 		t1 = ((-1) * b + sqrt(discr)) / (2 * a);
// 		t2 = ((-1) * b - sqrt(discr)) / (2 * a);
// 		printf("t1, t2 = %f , %f\n", t1, t2);
// 		if (t1 >= 1 || t2 >= 1)
// 		{
// 			if (t1 >= 1 && t2 >= 1)
// 			{
// 				if (t1 < t2)
// 				{
// 					t_min = t1;
// 					t_min2 = t2;
// 				}
// 				else
// 				{
// 					t_min = t2;
// 					t_min2 = t1;
// 				}
// 			}
// 			else
// 			{
// 				if (t1 >= 1)
// 				{
// 					t_min = t1;
// 					t_min2 = t2;
// 				}
// 				else
// 				{
// 					t_min = t2;
// 					t_min2 = t1;
// 				}
// 			}
// 		}
// 		else
// 			return ;

// 		cy_dot.x = new_op.x * t_min + new_o.x;
// 		cy_dot.y = new_op.y * t_min + new_o.y;
// 		cy_dot.z = new_op.z * t_min + new_o.z;

// 		if (cy_dot.z < (-0.5) * hei || cy_dot.z > hei * (0.5))
// 			t_min = t_min2;

// 		cy_dot.x = new_op.x * t_min + new_o.x;
// 		cy_dot.y = new_op.y * t_min + new_o.y;
// 		cy_dot.z = new_op.z * t_min + new_o.z;
// 		if (cy_dot.z < (-0.5) * hei || cy_dot.z > hei * (0.5))
// 			return ;
// 		vec_fill(&norm, cy_dot.x, cy_dot.y, 0);
// 		normalize2(&norm, norm);
// 		*min_t = t_min;
// 		*min_color = cy->color;
// 	}
// 	// if (*min_t == -1 || t_min < *min_t)
// 	// {

// 		*min_t = t_min;
// 		// printf("ok\n");
// 		*min_color = cy->color;
// 		// fill_color(min_color, 255, 0, 0);
// 		*min_color = get_ligth_cylinder(cy, cy_dot, norm, *min_color, sc->light);
// 	// }			
// }
