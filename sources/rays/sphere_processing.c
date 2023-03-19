/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:48:40 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 15:48:41 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	sphere_param(t_kostyl *ko, t_scene *sc)
{
	t_point		sp_dot;
	t_point		norm;

	(*ko).min_color = ko->fig->color;
	get_ray_dot(&sp_dot, ko->ray, ko->min_t);
	vec_fill(&norm, sp_dot.x - ko->fig->fig.sp.coord.x,
		sp_dot.y - ko->fig->fig.sp.coord.y,
		sp_dot.z - ko->fig->fig.sp.coord.z);
	normalize2(&norm, norm);
	(*ko).min_color = compute_color(sc, ko->fig, ko->ray.op, sp_dot);
}

void	sphere_processing(t_kostyl *ko, t_scene *scene)
{
	double	t;

	t = is_sphere(ko->ray, ko->fig, 1);
	if ((ko->min_t == -1 || t < ko->min_t) && t > 1)
	{
		(*ko).min_t = t;
		sphere_param(ko, scene);
	}
}
