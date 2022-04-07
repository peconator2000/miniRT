/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:29:10 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:29:53 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_scene(t_scene	*scene)
{
	scene->resolution[0] = 0;
	scene->resolution[1] = 0;
	scene->a_light = 0.0;
	scene->al_color = create_color(0, 0, 0);
	scene->figs = NULL;
}

static void	init_camera(t_camera *cam)
{
	cam->view_size[0] = 0;
	cam->view_size[1] = 0;
	cam->deg = 90;
	vec_fill(&(cam->pos), 0, 0, 0);
	vec_fill(&(cam->no_vec), 0, 0, 0);
	vec_fill(&(cam->new_pos), 0, 0, 0);
}

void	init_mlx(t_minirt *minirt)
{
	int	width;
	int	height;

	minirt->mlx = mlx_init();
	width = minirt->scene->resolution[0];
	height = minirt->scene->resolution[1];
	minirt->win = mlx_new_window(minirt->mlx, width, height, "miniRT");
	minirt->img->img = mlx_new_image(minirt->mlx, width, height);
	minirt->img->addr = mlx_get_data_addr(minirt->img->img,
			&(minirt->img->bits_per_pixel),
			&(minirt->img->line_length), &(minirt->img->endian));
}

t_minirt	*init(void)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)err_malloc(sizeof(t_minirt));
	minirt->scene = (t_scene *)err_malloc(sizeof(t_scene));
	minirt->scene->camera = (t_camera *)err_malloc(sizeof(t_camera));
	minirt->scene->light = (t_light *)err_malloc(sizeof(t_light));
	minirt->img = (t_image *)err_malloc(sizeof(t_image));
	init_scene(minirt->scene);
	init_camera(minirt->scene->camera);
	minirt->scene->camera->deg = 0;
	minirt->scene->light->color.r = 255;
	minirt->scene->light->color.g = 255;
	minirt->scene->light->color.b = 255;
	minirt->scene->light->bri = 0.0;
	return (minirt);
}
