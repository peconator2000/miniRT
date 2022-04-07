/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shpere_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:24:29 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 00:27:13 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_valid_param(t_equ *equ, double md)
{
	if ((*equ).t1 >= md || (*equ).t2 >= md)
	{
		if ((*equ).t1 >= md && (*equ).t2 >= md)
		{
			if ((*equ).t1 < (*equ).t2)
				(*equ).t_min = (*equ).t1;
			else
				(*equ).t_min = (*equ).t2;
		}
		else
		{
			if ((*equ).t1 >= md)
				(*equ).t_min = (*equ).t1;
			else
				(*equ).t_min = (*equ).t2;
		}
	}
	else
		return (0);
	return (1);
}

void	get_ray_dot(t_point *res_dot, t_ray ray, double t_min)
{
	t_point	dir;
	t_point	dot;

	dir = ray.op;
	dot = ray.o;
	(*res_dot).x = dir.x * t_min + dot.x;
	(*res_dot).y = dir.y * t_min + dot.y;
	(*res_dot).z = dir.z * t_min + dot.z;
}

void	ray_fill(t_ray *res, t_point o, t_point p)
{
	(*res).op.x = p.x - o.x;
	(*res).op.y = p.y - o.y;
	(*res).op.z = p.z - o.z;
	(*res).o = o;
	(*res).p = p;
}

double	is_sphere(t_ray ray, t_figures *sp, double md)
{
	t_point	s;
	t_equ	equ;
	double	rad;

	s = sp->fig.sp.coord;
	rad = sp->fig.sp.diameter * 0.5;
	equ.t_min = -1;
	equ.a = ray.op.x * ray.op.x + ray.op.y * ray.op.y + ray.op.z * ray.op.z;
	equ.b = 2 * (ray.op.x * (ray.o.x - s.x)
			+ ray.op.y * (ray.o.y - s.y) + ray.op.z * (ray.o.z - s.z));
	equ.c = ((ray.o.x - s.x) * (ray.o.x - s.x)
			+ (ray.o.y - s.y) * (ray.o.y - s.y)
			+ (ray.o.z - s.z) * (ray.o.z - s.z) - rad * rad);
	equ.discr = equ.b * equ.b - 4 * equ.a * equ.c;
	equ.t1 = (equ.b * (-1) + sqrt(equ.discr)) / (2 * equ.a);
	equ.t2 = (equ.b * (-1) - sqrt(equ.discr)) / (2 * equ.a);
	if (!is_valid_param(&equ, md))
		return (-1);
	return (equ.t_min);
}

double	is_cy_sphere(t_ray ray, t_figures *sp, t_point k, double md)
{
	t_point	s;
	t_equ	equ;
	double	rad;

	get_cy_basis_dot(sp->fig.sp.coord, &s, sp, k);
	rad = sp->fig.sp.diameter * 0.5;
	equ.t_min = -1;
	equ.a = ray.op.x * ray.op.x + ray.op.y * ray.op.y + ray.op.z * ray.op.z;
	equ.b = 2 * (ray.op.x * (ray.o.x - s.x)
			+ ray.op.y * (ray.o.y - s.y) + ray.op.z * (ray.o.z - s.z));
	equ.c = ((ray.o.x - s.x) * (ray.o.x - s.x)
			+ (ray.o.y - s.y) * (ray.o.y - s.y)
			+ (ray.o.z - s.z) * (ray.o.z - s.z) - rad * rad);
	equ.discr = equ.b * equ.b - 4 * equ.a * equ.c;
	equ.t1 = (equ.b * (-1) + sqrt(equ.discr)) / (2 * equ.a);
	equ.t2 = (equ.b * (-1) - sqrt(equ.discr)) / (2 * equ.a);
	if (!is_valid_param(&equ, md))
		return (-1);
	return (equ.t_min);
}
