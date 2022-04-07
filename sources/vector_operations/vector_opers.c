/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_opers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:33:18 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:34:44 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_distance(t_point start, t_point end)
{
	double	distance;

	distance = sqrt(pow(end.x - start.x, 2)
			+ pow(end.y - start.y, 2) + pow(end.z - start.z, 2));
	return (distance);
}

double	get_dot(t_point start, t_point end)
{
	return (start.x * end.x + start.y * end.y + start.z * end.z);
}

double	get_module(t_point start, t_point end)
{
	return (sqrt(get_dot(start, end)));
}

t_point	normalize(t_point point)
{
	t_point	normalized_vector;
	double	module;

	module = get_module(point, point);
	normalized_vector.x = point.x * pow(module, -1);
	normalized_vector.y = point.y * pow(module, -1);
	normalized_vector.z = point.z * pow(module, -1);
	return (normalized_vector);
}

void	normalize2(t_point *dot, t_point point)
{
	double	module;

	module = get_module(point, point);
	(*dot).x = point.x * pow(module, -1);
	(*dot).y = point.y * pow(module, -1);
	(*dot).z = point.z * pow(module, -1);
}
