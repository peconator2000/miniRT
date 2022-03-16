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
	t_figures	*figs;

	data = NULL;
	data = init();
	if (!parse(argc, argv, data) || !data)
		return (1);

	figs = data->scene->figs;
	// Вывод данных фигур
	while (figs)
	{
		if (figs->type == PLANE) {
			printf("PLANE: x = %f, y = %f, z = %f\nno_vec.x = %f, no_vec.y = %f, no_vec.z = %f\ncolor = %d",
					figs->fig.pl.coord.x, figs->fig.pl.coord.y, figs->fig.pl.coord.z, figs->no_vec.x, figs->no_vec.y, figs->no_vec.z, figs->color);
		} else if (figs->type == SPHERE) {
			printf("SPHERE: x = %f, y = %f, z = %f\ndiameter = %f\ncolor = %d",
					figs->fig.sp.coord.x, figs->fig.sp.coord.y, figs->fig.sp.coord.z, figs->fig.sp.diameter,figs->color);
		} else if (figs->type == CYLINDER) {
			printf("CYLINDER: x = %f, y = %f, z = %f\nno_vec.x = %f, no_vec.y = %f, no_vec.z = %f\ncolor = %d\ndiameter = %f, height = %f\n",
					figs->fig.cy.coord.x, figs->fig.cy.coord.y, figs->fig.cy.coord.z, figs->no_vec.x, figs->no_vec.y, figs->no_vec.z, figs->color, figs->fig.cy.diameter, figs->fig.cy.height);
		}
		printf("\n");
		figs = figs->next;
	}
	// //  Заполнени сферы для пробы----------------------------------------------------
	// data->scene->figs = init_sp();
	// printf(" sp.x = %f\n sp.y = %f\n sp.z = %f\n sp.diametr = %f",
	// 		data->scene->figs->fig.sp.coord.x, data->scene->figs->fig.sp.coord.y,
	// 		data->scene->figs->fig.sp.coord.z, data->scene->figs->fig.sp.diameter);
	// // TEMP ------------------------------------------------------------------------

	controller(data);
	return (0);
}
