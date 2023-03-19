/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:56 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 13:25:15 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	show_type(t_figures *fig, char *str)
{
	if (fig->type == SPHERE)
		printf("shpere %s\n", str);
	else if (fig->type == PLANE)
		printf("plane %s\n", str);
	else if (fig->type == CYLINDER)
		printf("cylinder %s\n", str);
}

static void	get_dist_to_obj(t_scene *scene, t_ray ray_fig,
		double *min_t)
{
	t_figures	*figs;

	figs = scene->figs;
	while (figs)
	{
		if (figs->type == SPHERE && (!(figs->is_check) || figs->in_dot))
			*min_t = is_sphere(ray_fig, figs, EPSILON);
		else if (figs->type == PLANE && (!(figs->is_check)))
			*min_t = is_plane(ray_fig, figs);
		else if (figs->type == CYLINDER && (!(figs->is_check)))
			*min_t = is_cylinder(ray_fig.o, ray_fig.p, figs, EPSILON);
		if (*min_t > EPSILON && *min_t < 1)
			return ;
		figs = figs->next;
	}
}

int	check_shadow(t_scene *scene, t_point intersect, t_figures *figure)
{
	t_ray	ray;
	double	dist;

	ray_fill(&ray, intersect, scene->light->coord);
	dist = -1;
	figure->is_check = 1;
	get_dist_to_obj(scene, ray, &dist);
	figure->is_check = 0;
	if (dist > EPSILON && dist < 1)
		return (1);
	return (0);
}
