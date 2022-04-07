/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:35:04 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:36:10 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vcos(t_point a, t_point b)
{
	return (get_dot(a, b) / (get_module(a, a) * get_module(b, b)));
}

double	vsin(t_point a, t_point b)
{
	return (sqrt(1 - pow(vcos(a, b), 2)));
}

t_point	vec_mult_coef(t_point vector, double coef)
{
	return (point_define(vector.x * coef, vector.y * coef, vector.z * coef));
}

t_point	reflect_ray(t_point ray, t_point normal)
{
	return (vector_subtract(vec_mult_coef(normal, 2
				* get_dot(normal, ray)), ray));
}
