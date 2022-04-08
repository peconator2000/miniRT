/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:44:06 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 15:44:14 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	for_norm(t_point *cy_dot, t_point *norm,
		t_ray new_ray, t_figures *cy)
{
	get_ray_dot(cy_dot, new_ray, cy->cy_t);
	vec_fill(norm, (*cy_dot).x, (*cy_dot).y, 0);
	normalize2(norm, *norm);
	back_world_basis(norm, cy);
	back_world_basis(cy_dot, cy);
	cy_normal(norm, cy->fig.cy.coord);
}

static void	cylinder_param(t_kostyl *ko, t_scene *sc, t_point dot)
{
	t_ray		new_ray;
	t_point		cy_dot;
	t_point		norm;

	get_cy_basis_dot(sc->camera->pos, &(new_ray.o),
		ko->fig, ko->fig->fig.cy.coord);
	get_cy_basis_dot(dot, &(new_ray.p), ko->fig, ko->fig->fig.cy.coord);
	ray_fill(&new_ray, new_ray.o, new_ray.p);
	normalize2(&(new_ray.op), new_ray.op);
	for_norm(&cy_dot, &norm, new_ray, ko->fig);
	get_ray_dot(&cy_dot, ko->ray, ko->min_t);
	(*ko).min_color = ko->fig->color;
	(*ko).min_color = compute_cy_color(sc, ko->fig, cy_dot, norm);
}

void	cylinder_processing(t_kostyl *ko, t_scene *scene, t_point dot)
{
	double	t;

	t = is_cylinder(scene->camera->pos, dot, ko->fig, 1);
	if ((ko->min_t == -1 || t < ko->min_t) && t > 1)
	{
		(*ko).min_t = t;
		cylinder_param(ko, scene, dot);
	}
}
