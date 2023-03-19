/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:30:46 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:30:50 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_cylinder(t_figures **figs, char **str, t_scene *scene)
{
	t_figures	*current_fig;

	add_figure(figs, new_figure(CYLINDER));
	current_fig = get_last_fig(*figs);
	current_fig->fig.scene = scene;
	skip_space(str);
	current_fig->fig.cy.coord = parse_point3(str);
	current_fig->no_vec = normalize(parse_point3(str));
	current_fig->fig.cy.diameter = str_to_double(str);
	current_fig->fig.cy.height = str_to_double(str);
	current_fig->in_dot = 0;
	current_fig->color = parse_color(str);
	current_fig->is_check = 0;
}

void	parse_sphere(t_figures **figs, char **str, t_scene *scene)
{
	t_figures	*current_fig;

	(void)scene;
	add_figure(figs, new_figure(SPHERE));
	current_fig = get_last_fig(*figs);
	skip_space(str);
	current_fig->fig.sp.coord = parse_point3(str);
	current_fig->fig.sp.diameter = str_to_double(str);
	current_fig->color = parse_color(str);
	current_fig->in_dot = 0;
	current_fig->is_check = 0;
}

void	parse_plane(t_figures **figs, char **str, t_scene *scene)
{
	t_figures	*current_fig;

	add_figure(figs, new_figure(PLANE));
	current_fig = get_last_fig(*figs);
	current_fig->fig.scene = scene;
	skip_space(str);
	current_fig->fig.pl.coord = parse_point3(str);
	current_fig->no_vec = normalize(parse_point3(str));
	current_fig->color = parse_color(str);
	current_fig->in_dot = 0;
	current_fig->is_check = 0;
}
