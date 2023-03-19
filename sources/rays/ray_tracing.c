/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:46:50 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 15:46:53 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_minimal_color(t_minirt *data, t_point dot, t_color *color)
{
	t_figures	*elems;
	t_kostyl	ko;

	elems = data->scene->figs;
	fill_color(color, 0, 0, 0);
	ko.min_color = *color;
	ko.min_t = -1;
	while (elems)
	{
		ray_fill(&(ko.ray), data->scene->camera->pos, dot);
		ko.fig = elems;
		if (elems->type == PLANE)
			plane_processing(&ko, data->scene);
		else if (elems->type == SPHERE)
			sphere_processing(&ko, data->scene);
		else if (elems->type == CYLINDER)
			cylinder_processing(&(ko), data->scene, dot);
		*color = ko.min_color;
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
