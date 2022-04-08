/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:25:47 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 13:51:55 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_cy_coord(t_figures *fig, t_point *dot)
{
	t_point	rig;
	t_point	up;
	t_point	dir;
	t_point	old;

	rig = fig->r;
	up = fig->u;
	dir = fig->d;
	old = *dot;
	(*dot).x = vec_scalar_mult(rig, old) + fig->fig.cy.coord.x;
	(*dot).y = vec_scalar_mult(up, old) + fig->fig.cy.coord.y;
	(*dot).z = vec_scalar_mult(dir, old) + fig->fig.cy.coord.z;
}

t_color	pixel_mix(double how, t_scene *sc, t_point dot, t_figures *fig)
{
	double	rgb[3];
	t_color	true_c;

	true_c = fig->color;
	ft_memset(rgb, 0, 3 * sizeof(double));
	add_coeficient(&rgb, sc->a_light, sc->al_color.mix);
	if (how < 0 || check_shadow(sc, dot, fig))
		;
	else
		add_coeficient(&rgb, how * sc->light->bri, sc->light->color.mix);
	fig->in_dot = 0;
	return (build_color(true_c.mix, rgb));
}

t_color	compute_color(t_scene *sc, t_figures *fig,
		t_point ray, t_point dot)
{
	t_point	norm;
	t_point	direction;
	double	how;

	norm = get_normal(fig, dot, ray);
	direction = normalize(vector_subtract(sc->light->coord, dot));
	how = vec_scalar_mult(norm, direction);
	return (pixel_mix(how, sc, dot, fig));
}

t_color	compute_cy_color(t_scene *sc, t_figures *fig, t_point dot, t_point norm)
{
	t_point	direction;
	double	how;

	direction = normalize(vector_subtract(sc->light->coord, dot));
	normalize2(&direction, direction);
	if (fig->in_dot)
		vec_mult_num(&norm, -1);
	how = vec_scalar_mult(norm, direction);
	return (pixel_mix(how, sc, dot, fig));
}
