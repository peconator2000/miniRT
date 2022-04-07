/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:52 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 22:35:30 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_cy_coord(t_figures *fig, t_point *dot)
{
	t_point	rig;
	t_point	up;
	t_point	dir;
	t_point old;

	rig = fig->r;
	up = fig->u;
	dir = fig->d;
	old = *dot;
	(*dot).x = vec_scalar_mult(rig, old) + fig->fig.cy.coord.x;
	(*dot).y = vec_scalar_mult(up, old) + fig->fig.cy.coord.y;
	(*dot).z = vec_scalar_mult(dir, old) + fig->fig.cy.coord.z;
}

// t_color	color_moves(t_scene *scene, t_figures *figure,t_point intersect, t_point normal)
// {
	
// }


// t_color	compute_cy_color(t_scene *scene, t_figures *figure,t_point intersect, t_point normal)
// {
// 	t_point	direction;
// 	double	rgb[3];
// 	t_color new_color;
// 	t_color	true_color = figure->color;
// 	double how;
// 	t_light light;

// 	ft_memset(rgb, 0, 3 * sizeof(double));
// 	light = *(scene->light);
// 	direction = normalize(vector_subtract(scene->light->coord, intersect));
// 	normalize2(&direction, direction);
// 	if (figure->in_dot)
// 	{
// 		vec_mult_num(&normal, -1);
// 	}
// 		how = vec_scalar_mult(normal, direction);
// 		if (how < 0 || check_shadow(scene, intersect, figure))
// 		{
// 			new_color.r = true_color.r * (0.2);
// 			new_color.g = true_color.g * (0.2);
// 			new_color.b = true_color.b * (0.2);
// 			new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
// 			return (new_color);
// 		}
// 		new_color.r = true_color.r * (0.2) + true_color.r  * (how *  light.bri);
// 		new_color.g = true_color.g * (0.2) + true_color.g  * (how * light.bri);
// 		new_color.b = true_color.b * (0.2) + true_color.b * (how * light.bri);
// 		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
// 	return (new_color);
// }



t_color c_without_how(t_color true_c, t_scene *sc)
{
	t_color new_c;
	t_color al_c;
	double	al_i;

	al_c = sc->al_color;
	al_i = sc->a_light;	
	new_c.r = true_c.r * al_i;
	new_c.g = true_c.g * al_i;
	new_c.b = true_c.b * al_i;
	if (new_c.r > 255)
		new_c.r = 255;
	if (new_c.g > 255)
		new_c.g = 255;
	if (new_c.b > 255)
		new_c.b = 255;
	new_c.mix =((new_c.r << 16) | (new_c.g << 8) | new_c.b);
	return (new_c);
}

t_color c_with_how(t_color true_c, double how, t_scene *sc)
{
	t_color al_c;
	t_color new_c;
	t_light lig;
	double	al_i;

	al_i = sc->a_light;
	al_c = sc->al_color;
	new_c.r = true_c.r * al_i + true_c.r * (how * (lig.bri + al_i))/ 255;
	new_c.g = true_c.g * al_i + true_c.g * (how * (lig.bri + al_i))/ 255;
	new_c.b = true_c.b * al_i + true_c.b * (how * (lig.bri + al_i))/ 255;

	if (new_c.r > 255)
		new_c.r = 255;
	if (new_c.g > 255)
		true_c.g = 255;
	if (true_c.b > 255)
		true_c.b = 255;
	new_c.mix =((true_c.r << 16) | (true_c.g << 8) | true_c.b);
	return (new_c);
}

t_color	pixel_mix(double how, t_scene *sc, t_point dot, t_figures *fig)
{
	t_color true_c;

	true_c = fig->color;
	if (how < 0 || check_shadow(sc, dot, fig))
		return(c_without_how(true_c, sc));
	return (c_with_how(true_c, how, sc));
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



// t_color	compute_cy_color(t_scene *scene, t_figures *figure,t_point intersect, t_point normal)
// {
// 	t_point	direction;
// 	double	rgb[3];
// 	t_color new_color;
// 	t_color	true_color = figure->color;
// 	double how;
// 	t_light light;

// 	ft_memset(rgb, 0, 3 * sizeof(double));
// 	light = *(scene->light);
// 	direction = normalize(vector_subtract(scene->light->coord, intersect));
// 	normalize2(&direction, direction);
// 	if (figure->in_dot)
// 	{
// 		vec_mult_num(&normal, -1);
// 	}
// 		how = vec_scalar_mult(normal, direction);
// 		if (how < 0 || check_shadow(scene, intersect, figure))
// 		{
// 			new_color.r = true_color.r * (0.2);
// 			new_color.g = true_color.g * (0.2);
// 			new_color.b = true_color.b * (0.2);
// 			new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
// 			return (new_color);
// 		}
// 		new_color.r = true_color.r * (0.2) + true_color.r  * (how *  light.bri);
// 		new_color.g = true_color.g * (0.2) + true_color.g  * (how * light.bri);
// 		new_color.b = true_color.b * (0.2) + true_color.b * (how * light.bri);
// 		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
// 	return (new_color);
// }

// t_color	compute_color(t_scene *scene, t_figures *figure,
// 		t_point ray, t_point dot)
// {
// 	t_point	normal;
// 	t_point	direction;
// 	double	rgb[3];
// 	t_color new_color;
// 	t_color	true_color = figure->color;
// 	double how;
// 	t_light light;

// 	ft_memset(rgb, 0, 3 * sizeof(double));
// 	light = *(scene->light);
// 	normal = get_normal(figure, dot, ray);
// 	direction = normalize(vector_subtract(scene->light->coord, dot));
// 	how = vec_scalar_mult(normal, direction);
// 	if (how < 0 || check_shadow(scene, dot, figure))
// 	{
// 		new_color.r = true_color.r * (0.2);
// 		if (new_color.r > 255)
// 			new_color.r = 255;
// 		new_color.g = true_color.g * (0.2);
// 		if (new_color.g > 255)
// 			new_color.g = 255;
// 		new_color.b = true_color.b * (0.2);
// 		if (new_color.b > 255)
// 			new_color.b = 255;
// 		new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
// 		return (new_color);
// 	}
// 	new_color.r = true_color.r * (0.2) + true_color.r  * (how *  light.bri);
// 	new_color.g = true_color.g * (0.2) + true_color.g  * (how * light.bri);
// 	if (new_color.r > 255)
// 		new_color.r = 255;
// 	if (new_color.g > 255)
// 		new_color.g = 255;
// 	new_color.b = true_color.b * (0.2) + true_color.b * (how * light.bri);
// 	if (new_color.b > 255)
// 		new_color.b = 255;
// 	new_color.mix =((new_color.r << 16) | (new_color.g << 8) | new_color.b);
// 	return (new_color);
// }
