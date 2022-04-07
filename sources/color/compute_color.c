/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:52 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:17:52 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void get_cy_coord(t_figures *fig, t_point *dot)
{
	t_point	rig;
	t_point	up;
	t_point	dir;

	rig = fig->r;
	up = fig->u;
	dir = fig->d;
	(*dot).x = rig.x * (*dot).x + rig.y * (*dot).y + rig.z * (*dot).z + fig->fig.cy.coord.x;
	(*dot).y = up.x * (*dot).x + up.y * (*dot).y + up.z * (*dot).z  + fig->fig.cy.coord.y;
	(*dot).z = dir.x * (*dot).x + dir.y * (*dot).y + dir.z * (*dot).z + fig->fig.cy.coord.z;
}

t_color	compute_cy_color(t_scene *scene, t_figures *figure,
		t_point ray, double dist, t_point intersect, t_point normal)
{
	t_point	direction;
	double	rgb[3];
	t_color new_color;
	t_color	true_color = figure->color;
	double how;
	t_light light;

	ft_memset(rgb, 0, 3 * sizeof(double));
	(void)dist;
	(void)ray;
	light = *(scene->light);
	direction = normalize(vector_subtract(scene->light->coord, intersect));
	normalize2(&direction, direction);
	if (figure->in_dot)
	{
		vec_mult_num(&normal, -1);
	}
		how = vec_scalar_mult(normal, direction);
		if (how < 0 || check_shadow(scene, intersect, figure))
		{
			new_color.r = true_color.r * (0.2);
			new_color.g = true_color.g * (0.2);
			new_color.b = true_color.b * (0.2);
			new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
			return (new_color);
		}
		new_color.r = true_color.r * (0.2) + true_color.r  * (how *  light.bri);
		new_color.g = true_color.g * (0.2) + true_color.g  * (how * light.bri);
		new_color.b = true_color.b * (0.2) + true_color.b * (how * light.bri);
		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
	return (new_color);
}

t_color	compute_color(t_scene *scene, t_figures *figure,
		t_point ray, double dist, t_point intersect)
{
	t_point	normal;
	t_point	direction;
	double	rgb[3];
	t_color new_color;
	t_color	true_color = figure->color;
	double how;
	t_light light;

	ft_memset(rgb, 0, 3 * sizeof(double));
	(void)dist;
	light = *(scene->light);
	normal = get_normal(figure, intersect, ray);
	direction = normalize(vector_subtract(scene->light->coord, intersect));
	how = vec_scalar_mult(normal, direction);
	if (how < 0 || check_shadow(scene, intersect, figure))
	{
		new_color.r = true_color.r * (0.2);
		if (new_color.r > 255)
			new_color.r = 255;
		new_color.g = true_color.g * (0.2);
		if (new_color.g > 255)
			new_color.g = 255;
		new_color.b = true_color.b * (0.2);
		if (new_color.b > 255)
			new_color.b = 255;
		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
		return (new_color);
	}
	new_color.r = true_color.r * (0.2) + true_color.r  * (how *  light.bri);
	new_color.g = true_color.g * (0.2) + true_color.g  * (how * light.bri);
	if (new_color.r > 255)
		new_color.r = 255;
	if (new_color.g > 255)
		new_color.g = 255;
	new_color.b = true_color.b * (0.2) + true_color.b * (how * light.bri);
	if (new_color.b > 255)
		new_color.b = 255;
	new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
	return (new_color);
}
