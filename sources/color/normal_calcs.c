/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:50 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 13:24:38 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_point	get_normal(t_figures *figure, t_point intersect, t_point ray)
{
	t_point	normal;

	normal = point_define(0, 0, 0);
	if (figure->type == PLANE)
		normal = normalize(figure->no_vec);
	if (figure->type == SPHERE)
		normal = normalize(vector_subtract(intersect, figure->fig.sp.coord));
	if (get_dot(normal, ray) > 0)
	{
		normal = vector_nmultiply(normal, -1);
		figure->in_dot = 1;
	}
	normal = normalize(normal);
	return (normal);
}
