/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:18:11 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 21:18:55 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_pl_t(t_point n, t_ray ray, t_point k)
{
	double	num;
	double	den;
	double	d;

	d = n.x * k.x + n.y * k.y + n.z * k.z;
	num = d - (n.x * ray.o.x + n.y * ray.o.y + n.z * ray.o.z);
	den = n.x * ray.op.x + n.y * ray.op.y + n.z * ray.op.z;
	if (den == 0)
		return (-1);
	return (num / den);
}

double	is_plane(t_ray ray, t_figures *pl)
{
	t_point	n;
	t_point	k;

	n = pl->no_vec;
	k = pl->fig.pl.coord;
	return (get_pl_t(n, ray, k));
}

double	is_cy_plane(t_ray ray, t_figures *pl, t_point k)
{
	t_point	n;
	t_point	r;

	get_cy_basis_dot(pl->fig.pl.coord, &r, pl, k);
	get_cy_basis_dot(pl->no_vec, &n, pl, k);
	return (get_pl_t(n, ray, r));
}
