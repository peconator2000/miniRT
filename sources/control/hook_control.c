#include "miniRT.h"

int	key_hook(int keycode, t_minirt *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		free_minirt(data);
		exit(0);
	}
	else if (keycode == 124)//rigth
	{
		data->scene->camera->pos.x += STEP;
		draw_figures(data);
	}
	else if (keycode == 123)//left
	{
		data->scene->camera->pos.x -= STEP;
		draw_figures(data);
	}
	else if (keycode == 125)//down
	{
		data->scene->camera->pos.z -= STEP;
		draw_figures(data);
	}
	else if (keycode == 126)//up
	{
		data->scene->camera->pos.z += STEP;
		draw_figures(data);
	}
	else if (keycode == 13)
	{
		data->scene->camera->pos.y += STEP;
		draw_figures(data);
	}
	else if (keycode == 1)
	{
		data->scene->camera->pos.y -= STEP;
		draw_figures(data);
	}
	return (1);
}

int	cross_icon(int key)
{
	(void)key;
	exit(0);
	return (0);
}

void	controller(t_minirt *data)
{
	draw_figures(data);
	// my_mlx_pixel_put(data->img, 100, 100, data->scene->figs->color.mix);
	// draw_all();
	mlx_hook(data->win, 17, 0, &cross_icon, (void *)data);
	mlx_key_hook(data->win, &key_hook, (void *)data);
	mlx_loop(data->mlx);
}
