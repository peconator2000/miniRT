/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:46:12 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 15:46:54 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	plane_param(t_kostyl *ko, t_scene *sc)
{
	t_point		pl_dot;
	t_point		norm;

	(*ko).min_color = ko->fig->color;
	get_ray_dot(&pl_dot, ko->ray, ko->min_t);
	vec_fill(&norm, ko->fig->no_vec.x, ko->fig->no_vec.y, ko->fig->no_vec.z);
	normalize2(&norm, norm);
	(*ko).min_color = compute_color(sc, ko->fig, ko->ray.op, pl_dot);
}

void	plane_processing(t_kostyl *ko, t_scene *scene)
{
	double	t;

	t = is_plane(ko->ray, ko->fig);
	if ((ko->min_t == -1 || t < ko->min_t) && t > 1)
	{
		(*ko).min_t = t;
		plane_param(ko, scene);
	}
}
