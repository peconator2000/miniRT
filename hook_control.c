#include "minirt.h"

int	key_hook(int keycode, t_screen *scr)
{
	if (keycode == 53)
	{
		mlx_destroy_window(scr->init, scr->win);
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

void	controller(t_data *data)
{
	mlx_loop_hook(data->scr->init, &draw_figures, (void *)data);
	mlx_hook(data->scr->win, 17, 0, &cross_icon, (void *)data);
	mlx_key_hook(data->scr->win, &key_hook, (void *)data);
	mlx_loop(data->scr->init);
}