#include "miniRT.h"

void	show_vec(char *str, t_point vec)
{
	printf("%s (%f, %f, %f)\n", str, vec.x, vec.y, vec.z);
}

void	get_new_cylinder_basis(t_figures *cy)
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

double	get_matrix_determinant(t_point r, t_point u, t_point d)
{
	double	res;

	res = r.x * (u.y * d.z - u.z * d.y);
	res -= r.y * (u.x * d.z - d.x * u.z);
	res += r.z * (u.x * d.y - d.x * u.y);
	return (res);
}

void	get_cy_basis_dot(t_point dot, t_point *new, t_figures *fig, t_point k)
{
	double det;
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

void	back_world_basis(t_point *dot, t_figures *fig)
{
	t_point	rig;
	t_point	up;
	t_point	dir;
	t_point	old;

	rig = fig->r;
	up = fig->u;
	dir = fig->d;
	old = *dot;
	(*dot).x = vec_scalar_mult(rig, old) + fig->fig.cy.coord.x;
	(*dot).y = vec_scalar_mult(up, old) + fig->fig.cy.coord.y;
	(*dot).z = vec_scalar_mult(dir, old) + fig->fig.cy.coord.z;
}

void	swap_t(t_equ *equ)
{
	double	mid;

	if ((*equ).t2 < (*equ).t1)
	{
		mid = (*equ).t1;
		(*equ).t1 = (*equ).t2;
		(*equ).t2 = mid;
	}
}

int	rem_cylinder(t_ray ray, double t_min, double hei)
{
	t_point cy_dot;

	get_ray_dot(&cy_dot, ray, t_min);
	if (cy_dot.z < (-0.5) * hei || cy_dot.z > hei * (0.5))
		return (1);
	return (0);
}

int	is_valid_cy_param(t_equ *equ, double ed)
{
	double t1 = equ->t1;
	double t2 = equ->t2;
	double t_min;

	if (t1 >= ed || t2 >= ed)
	{
		if (t1 >= ed && t2 >= ed)
		{
			if (t1 < t2)
				t_min = t1;
			else
				t_min = t2;
		}
		else
		{
			if (t1 >= ed)
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

void	in_dot_checker(t_figures *cy, t_ray new_ray, double hei)
{
	t_point cam;

	cam = new_ray.o;
	if (sqrt(cam.x * cam.x + cam.y * cam.y) >= cy->fig.cy.diameter * (0.5))
		return ;
	(void)hei;
	cy->in_dot = 1;
}

double	get_cy_t(t_equ equ, double hei, t_ray new_ray, t_figures *cy, t_ray ray, double md)
{
	double	t_min;
	double	w_t_min;
	t_point cy_dot;

	equ.t1 = ((-1) * equ.b + sqrt(equ.discr)) / (2 * equ.a);
	equ.t2 = ((-1) * equ.b - sqrt(equ.discr)) / (2 * equ.a);
	swap_t(&equ);
	cy->in_dot = 0;
	in_dot_checker(cy, new_ray, hei);
	if (!is_valid_cy_param(&equ, md))
		return (-1);
	t_min = equ.t_min;
	if (rem_cylinder(new_ray, t_min, hei))
	{
		t_min = equ.t2;
		cy->in_dot = 1;
	}
	if (rem_cylinder(new_ray, t_min, hei))
		return (-1);
	get_ray_dot(&cy_dot, new_ray, t_min);
	back_world_basis(&cy_dot, cy);
	if (ray.op.x != 0)
		w_t_min = (cy_dot.x - ray.o.x) / ray.op.x;
	else if (ray.op.y != 0)
		w_t_min = (cy_dot.y - ray.o.y) / ray.op.y;
	else
		w_t_min = (cy_dot.z - ray.o.z) / ray.op.z;
	cy->cy_t = t_min;
	return (w_t_min);
}

double is_cylinder(t_point o, t_point p, t_figures *cy, double md)
{
	t_ray	new_ray;
	t_ray	ray;
	t_equ	equ;
	double	rad;
	double	hei;

	ray_fill(&ray, o, p);
	cy->in_dot = 0;
	hei = cy->fig.cy.height;
	rad = cy->fig.cy.diameter * (0.5);
	get_new_cylinder_basis(cy);
	get_cy_basis_dot(p, &(new_ray.p), cy, cy->fig.cy.coord);
	get_cy_basis_dot(o, &(new_ray.o), cy, cy->fig.cy.coord);
	ray_fill(&new_ray, new_ray.o, new_ray.p);
	normalize2(&(new_ray.op), new_ray.op);
	equ.a = new_ray.op.x * new_ray.op.x + new_ray.op.y * new_ray.op.y;
	equ.b = 2 * new_ray.op.x * new_ray.o.x + 2 * new_ray.op.y * new_ray.o.y;
	equ.c = new_ray.o.x * new_ray.o.x + new_ray.o.y * new_ray.o.y - rad * rad;
	equ.discr = equ.b * equ.b - 4 * equ.a * equ.c;
	if (equ.discr < 0)
		return (-1);
	if (fabs(equ.a) < EPSILON)
		return (-1);
	return (get_cy_t(equ, hei, new_ray, cy, ray, md));
}
