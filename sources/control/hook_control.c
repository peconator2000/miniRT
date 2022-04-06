/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:44:47 by vellie            #+#    #+#             */
/*   Updated: 2022/04/06 16:37:19 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	back_forth(int keycode, t_minirt *data)
{
	if (keycode == 125)
	{
		data->scene->light->coord.z -= STEP;
		draw_figures(data);
	}
	else if (keycode == 126)
	{
		data->scene->light->coord.z += STEP;
		draw_figures(data);
	}
}

static void	rigth_left(int keycode, t_minirt *data)
{
	if (keycode == 124)
	{
		// data->scene->camera->pos.x += STEP;
		data->scene->light->coord.x += STEP;
		draw_figures(data);
	}
	else if (keycode == 123)
	{
		// data->scene->camera->pos.x -= STEP;
		data->scene->light->coord.x -= STEP;
		draw_figures(data);
	}
}

static void	up_down(int keycode, t_minirt *data)
{
	if (keycode == 13)
	{
		// data->scene->camera->pos.y += STEP;
		data->scene->light->coord.y += STEP;
		draw_figures(data);
	}
	else if (keycode == 1)
	{
		// data->scene->camera->pos.y -= STEP;
		data->scene->light->coord.y -= STEP;
		draw_figures(data);
	}
}

int	key_hook(int keycode, t_minirt *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		free_minirt(data);
		exit(0);
	}
	back_forth(keycode, data);
	rigth_left(keycode, data);
	up_down(keycode, data);
	return (1);
}

int	cross_icon(int key)
{
	(void)key;
	exit(0);
	return (0);
}
