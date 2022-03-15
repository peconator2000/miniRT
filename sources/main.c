#include "miniRT.h"

t_figures *init_sp()
{
	t_figures *figs = err_malloc(sizeof(t_figures));
	figs->fig.sp.coord = point_define(400, 600, 0);
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

	// TEMP ------------------------------------------------------------------------
	data->scene->figs = init_sp();
	printf(" sp.x = %f\n sp.y = %f\n sp.z = %f\n sp.diametr = %f",
			data->scene->figs->fig.sp.coord.x, data->scene->figs->fig.sp.coord.y,
			data->scene->figs->fig.sp.coord.z, data->scene->figs->fig.sp.diameter);
	// TEMP ------------------------------------------------------------------------

	controller(data);
	return (0);
}
