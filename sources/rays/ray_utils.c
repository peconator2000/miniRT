/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:48:53 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 16:09:15 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cy_normal(t_point *normal, t_point cy_coord)
{
	(*normal).x -= cy_coord.x;
	(*normal).y -= cy_coord.y;
	(*normal).z -= cy_coord.z;
}

void	swap_t(t_equ *equ)
{
	double	mid;

	if ((*equ).t2 < (*equ).t1)
	{
		mid = (*equ).t1;
		(*equ).t1 = (*equ).t2;
		(*equ).t2 = mid;
	}
}

void	in_dot_checker(t_figures *cy, t_ray new_ray, double hei)
{
	t_point	cam;

	cam = new_ray.o;
	if (sqrt(cam.x * cam.x + cam.y * cam.y) >= cy->fig.cy.diameter * (0.5))
		return ;
	(void)hei;
	cy->in_dot = 1;
}
