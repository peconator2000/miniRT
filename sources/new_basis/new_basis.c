/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_basis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:54:29 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:55:09 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_norm(t_point *dot)
{
	double	len;

	len = pow((*dot).x, 2) + pow((*dot).y, 2) + pow((*dot).z, 2);
	(*dot).x = (*dot).x * pow(len, -1);
	(*dot).y = (*dot).y * pow(len, -1);
	(*dot).z = (*dot).z * pow(len, -1);
}

void	get_d(t_camera *cam)
{
	vec_fill(&(cam->dir), cam->no_vec.x, cam->no_vec.y, cam->no_vec.z);
}

void	get_r(t_camera *cam)
{
	t_point	tmp;

	if (cam->dir.x == 0 && cam->dir.z == 0)
		vec_fill(&tmp, -1, 0, 0);
	else
		vec_fill(&tmp, 0, 1, 0);
	if (cam->dir.y == 1 || cam->dir.y == -1)
	{
		if (cam->dir.y == 1)
			vec_fill(&(cam->rigth), 1, 0, 0);
		else
			vec_fill(&(cam->rigth), -1, 0, 0);
	}
	else
		vec_mult_vec(&(cam->rigth), tmp, cam->dir);
	vec_mult_vec(&(cam->up), cam->dir, cam->rigth);
}

void	new_basis(t_scene *scene)
{
	get_d(scene->camera);
	vec_mult_num(&(scene->camera->dir), -1);
	get_r(scene->camera);
	get_norm(&(scene->camera->dir));
	get_norm(&(scene->camera->up));
	get_norm(&(scene->camera->rigth));
}
