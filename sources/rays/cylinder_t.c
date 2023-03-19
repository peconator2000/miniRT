/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_t.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:21:43 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 16:31:39 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_valid_cy_param(t_equ *equ, double ed)
{
	double	t_min;

	if (equ->t1 >= ed || equ->t2 >= ed)
	{
		if (equ->t1 >= ed && equ->t2 >= ed)
		{
			if (equ->t1 < equ->t2)
				t_min = equ->t1;
			else
				t_min = equ->t2;
		}
		else
		{
			if (equ->t1 >= ed)
				t_min = equ->t1;
			else
				t_min = equ->t2;
		}
	}
	else
		return (0);
	equ->t_min = t_min;
	return (1);
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

static double	for_normik(t_equ *equ, t_figures *cy, t_ray new_ray)
{
	(*equ).t1 = ((-1) * equ->b + sqrt(equ->discr)) / (2 * equ->a);
	(*equ).t2 = ((-1) * equ->b - sqrt(equ->discr)) / (2 * equ->a);
	swap_t(equ);
	cy->in_dot = 0;
	in_dot_checker(cy, new_ray, cy->fig.cy.height);
	if (!is_valid_cy_param(equ, cy->fig.cy.md))
		return (-1.0);
	return (equ->t_min);
}

double	get_cy_t(t_equ equ, t_ray new_ray,
		t_figures *cy, t_ray ray)
{
	double	t_min;
	double	w_t_min;
	t_point	cy_dot;

	t_min = for_normik(&equ, cy, new_ray);
	if (t_min == -1.000)
		return (-1);
	if (rem_cylinder(new_ray, t_min, cy->fig.cy.height))
	{
		t_min = equ.t2;
		cy->in_dot = 1;
	}
	if (rem_cylinder(new_ray, t_min, cy->fig.cy.height))
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
