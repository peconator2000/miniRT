#include "miniRT.h"

int	key_hook(int keycode, t_minirt *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
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
	mlx_hook(data->win, 17, 0, &cross_icon, (void *)data);
	mlx_key_hook(data->win, &key_hook, (void *)data);
	mlx_loop(data->mlx);
}
