#include "miniRT.h"

// t_screen	*screen_init(void)
// {
// 	t_screen	*scr;
// 	int			len;
// 	int			high;

// 	len = 800;
// 	high = 1200;
// 	scr = malloc(sizeof(t_screen));
// 	scr->len = len;
// 	scr->high = high;
// 	scr->init = mlx_init();
// 	scr->win = mlx_new_window(scr->init, len, high, "miniRT");
// 	create_image(scr);
// 	return (scr);
// }


t_figures *init_sp()
{
	t_figures *figs = err_malloc(sizeof(t_figures));
	char *str_with_coord = ft_strdup("400,600,0");
	figs->fig.sp.coord = parse_point3(&str_with_coord);
	figs->fig.sp.diameter = 100.0;
	figs->type = 2;
	figs->next = NULL;
	return (figs);
}

int	main(int argc, char **argv)
{
	t_minirt	*data;

	data = NULL;
	data = init();
	if (!parse(argc, argv, data) || !data)
		return (1);
	printf("data->img->addr: %p\n", data->img->addr);
	data->scene->figs = init_sp();
	printf(" sp.x = %f\n sp.y = %f\n sp.z = %f\n sp.diametr = %f",
			data->scene->figs->fig.sp.coord.x, data->scene->figs->fig.sp.coord.y,
			data->scene->figs->fig.sp.coord.z, data->scene->figs->fig.sp.diameter);
	controller(data);
	return (0);
}
