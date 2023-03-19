/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:30:55 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:31:17 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_resolution(t_minirt *minirt, char **str)
{
	skip_space(str);
	minirt->scene->resolution[0] = str_to_int(str);
	check_range(minirt->scene->resolution[0], 1, INFINITY, "RESOLUTION");
	minirt->scene->resolution[1] = str_to_int(str);
	check_range(minirt->scene->resolution[1], 1, INFINITY, "RESOLUTION");
	init_mlx(minirt);
}

void	parse_ambient_light(t_minirt *minirt, char **str)
{
	skip_space(str);
	minirt->scene->a_light = str_to_double(str);
	check_range(minirt->scene->a_light, 0.0, 1.0, "AMBIENT LIGHT");
	minirt->scene->al_color = parse_color(str);
}

void	parse_light(t_minirt *minirt, char **str)
{
	skip_space(str);
	minirt->scene->light->coord = parse_point3(str);
	minirt->scene->light->bri = str_to_double(str);
	check_range(minirt->scene->light->bri, 0.0, 1.0, "LIGHT");
	minirt->scene->light->color = parse_color(str);
}

void	parse_camera(t_minirt *minirt, char **str)
{
	skip_space(str);
	minirt->scene->camera->pos = parse_point3(str);
	minirt->scene->camera->no_vec = normalize(parse_point3(str));
	skip_space(str);
	minirt->scene->camera->deg = str_to_int(str);
	check_range(minirt->scene->camera->deg, 0.0, 180.0, "CAMERA");
}
