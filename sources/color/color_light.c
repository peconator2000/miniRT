/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:43 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 19:32:45 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_light(t_ray v1, t_ray v2, t_figures *elem, t_color true_color, t_light *light)
{
	double	how;
	t_color	new_color;

	how = vec_scalar_mult(v1.op, v2.op);
	if (how < 0 || elem->in_dot)
	{
		new_color.r = true_color.r * (0.2);
		new_color.g = true_color.g * (0.2);
		new_color.b = true_color.b * (0.2);
		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);

		return (new_color);
	}
	new_color.r = true_color.r * (0.2) + true_color.r * light->color.r * (how *  light->bri * pow(255, -1));
	new_color.g = true_color.g * (0.2) + true_color.g * light->color.g * (how * light->bri * pow(255, -1));
	new_color.b = true_color.b * (0.2) + true_color.b * light->color.b * (how * light->bri * pow(255, -1));
	new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
	return (new_color);
}

t_color	get_light_sphere(t_figures *elem, t_point dot, t_color true_color, t_light *ligth)
{
	t_point	lig;
	t_point	cen;
	t_ray	l_dist;
	t_ray	norm;

	lig = ligth->coord;
	cen = elem->fig.sp.coord;
	ray_fill(&l_dist, dot, lig);
	ray_fill(&norm, cen, dot);
	normalize2(&(l_dist.op), l_dist.op);
	normalize2(&(norm.op), norm.op);
	return (get_light(l_dist, norm, elem, true_color, ligth));
}

t_color	get_light_cylinder(t_figures *elem, t_point dot, t_ray norm, t_color true_color, t_light *ligth)
{
	t_point	lig;
	t_ray	l_dist;

	lig = ligth->coord;
	get_cy_basis_dot(lig, &lig, elem, elem->fig.cy.coord);
	ray_fill(&l_dist, dot, lig);
	normalize2(&(l_dist.op), l_dist.op);
	return (get_light(l_dist, norm, elem, true_color, ligth));
}

t_color	get_light_plane(t_figures *elem, t_point dot, t_color true_color, t_light *ligth)
{
	t_point	lig;
	t_ray	l_dist;
	t_ray	norm;

	lig = ligth->coord;
	ray_fill(&l_dist, dot, lig);
	vec_fill(&(norm.o), 0, 0, 0);
	vec_fill(&(norm.p), elem->no_vec.x, elem->no_vec.y, elem->no_vec.z);
	ray_fill(&(norm), norm.o, norm.p);
	normalize2(&(l_dist.op), l_dist.op);
	normalize2(&(norm.op), norm.op);
	return (get_light(l_dist, norm, elem, true_color, ligth));
}
