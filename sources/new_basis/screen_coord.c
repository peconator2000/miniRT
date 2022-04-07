/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:54:22 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:58:14 by mwittenb         ###   ########.fr       */
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

	rig = cam->rigth;
	up = cam->up;
	dir = cam->dir;
	(*dot).x = rig.x * (*dot).x + rig.y * (*dot).y
		+ rig.z * (*dot).z + cam->pos.x;
	(*dot).y = up.x * (*dot).x + up.y * (*dot).y + up.z * (*dot).z + cam->pos.y;
	(*dot).z = dir.x * (*dot).x + dir.y * (*dot).y
		+ dir.z * (*dot).z + cam->pos.z;
}
