/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:54:22 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 21:28:35 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_new_sizes(t_scene *sc, double *delta)
{
	double	deg_rad;
	double	wid;
	double	hig;

	wid = sc->resolution[0];
	hig = sc->resolution[1];
	deg_rad = sc->camera->deg * M_PI * pow(180, -1) * 0.5;
	sc->camera->view_size[0] = 2 * tan(deg_rad);
	sc->camera->view_size[1] = 2 * tan(deg_rad) * hig * pow(wid, -1);
	*delta = 2 * tan(deg_rad) * pow(wid, -1);
}

void	get_inscreen(t_scene *sc, t_point *dot, double x, double y)
{
	static double	delta;

	if (!delta)
		get_new_sizes(sc, &delta);
	(*dot).x = (x) * delta;
	(*dot).y = (y) * delta;
	(*dot).z = -1;
}

void	get_new_coords(t_camera *cam, t_point *dot)
{
	t_point	rig;
	t_point	up;
	t_point	dir;
	t_point	old;

	rig = cam->rigth;
	up = cam->up;
	dir = cam->dir;
	old = *dot;
	(*dot).x = vec_scalar_mult(rig, old) + cam->pos.x;
	(*dot).y = vec_scalar_mult(up, old) + cam->pos.y;
	(*dot).z = vec_scalar_mult(dir, old) + cam->pos.z;
}
