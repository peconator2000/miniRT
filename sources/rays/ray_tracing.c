/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:19:04 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 23:48:51y mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_minimal_color(t_minirt *data, t_point dot, t_color *color)
{
	double		t;
	double		min_t;
	t_figures	*elems;
	t_ray		ray;

	elems = data->scene->figs;
	min_t = -1;
	fill_color(color, 0, 0, 0);
	while (elems)
	{
		ray_fill(&ray, data->scene->camera->pos, dot);
		if (elems->type == PLANE)
		{
			t = is_plane(ray, elems);
			if ((min_t == -1 || t < min_t) && t > 1)
			{
				min_t = t;
				plane_param(&min_t, color, elems, data->scene, ray);
			}
		}
		else if (elems->type == SPHERE)
		{
			t = is_sphere(ray, elems, 1);
			if ((min_t == -1 || t < min_t) && t > 1)
			{
				min_t = t;
				sphere_param(&min_t, color, elems, data->scene, ray);
			}
		}
		else if (elems->type == CYLINDER)
		{
			t = is_cylinder(data->scene->camera->pos, dot, elems, 1);
			if ((min_t == -1 || t < min_t) && t > 1)
			{
				min_t = t;
				cylinder_param(&min_t, color, elems, data->scene, dot, ray);
			}
		}
		elems = elems->next;
	}
}

int	get_color(t_minirt *data, double x_sc, double y_sc)
{
	t_color	color;
	t_point	dot;

	get_inscreen(data->scene, &dot, x_sc, y_sc);
	get_new_coords(data->scene->camera, &dot);
	get_minimal_color(data, dot, &color);
	return (color.mix);
}
