/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:56 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:25:03 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void show_type(t_figures *fig, char *str)
{
	if (fig->type == SPHERE)
		printf("shpere %s\n", str);
	else if (fig->type == PLANE)
		printf("plane %s\n", str);
	else if (fig->type == CYLINDER)
		printf("cylinder %s\n", str);
}

static void	get_dist_to_obj(t_scene *scene, t_ray ray_fig,
		double *closest_intersection)
{
	double		dist;
	t_figures	*figs;

	figs = scene->figs;
	dist = -1;
	while (figs)
	{
		if (figs->type == SPHERE && (!(figs->is_check)))
			*closest_intersection = is_sphere(ray_fig, figs, 0.00001);
		else if (figs->type == PLANE && (!(figs->is_check)))
			*closest_intersection = is_plane(ray_fig, figs);
		else if (figs->type == CYLINDER && (!(figs->is_check)))
			*closest_intersection = is_cylinder(ray_fig.o, ray_fig.p, figs, 0.00001);
		if (*closest_intersection > 0.00001 && *closest_intersection < 1)
			return ;
		figs = figs->next;
	}
}

int	check_shadow(t_scene *scene, t_point intersect, t_figures *figure)
{
	t_ray	ray;
	double	ray_len;
	double	dist;

	ray_fill(&ray, intersect, scene->light->coord);
	ray_len = get_module(ray.op, ray.op);
	dist = -1;
	figure->is_check = 1;
	get_dist_to_obj(scene, ray, &dist);
	figure->is_check = 0;
	if (dist == -1)
		return (0);
		(void)figure;
	if (dist > EPSILON && dist < 1)
		return (1);
	return (0);
}
