#include "miniRT.h"


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
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 800, 800, "miniRT");
	create_image(data);
	data->scene->figs = init_sp();
	controller(data);
	return (0);
}
