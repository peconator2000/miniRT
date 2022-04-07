/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_opers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:34:55 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:34:56 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_point	point_define(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point	vector_add(t_point start, t_point end)
{
	t_point	result_point;

	result_point.x = start.x + end.x;
	result_point.y = start.y + end.y;
	result_point.z = start.z + end.z;
	return (result_point);
}

t_point	vector_subtract(t_point start, t_point end)
{
	t_point	result_point;

	result_point.x = start.x - end.x;
	result_point.y = start.y - end.y;
	result_point.z = start.z - end.z;
	return (result_point);
}

t_point	vector_cross(t_point start, t_point end)
{
	t_point	cross_point;

	cross_point.x = start.y * end.z - start.z * end.y;
	cross_point.y = start.z * end.x - start.x * end.z;
	cross_point.z = start.x * end.y - start.y * end.x;
	return (cross_point);
}

t_point	vector_nmultiply(t_point p1, double n)
{
	return (point_define(p1.x * n, p1.y * n, p1.z * n));
}
