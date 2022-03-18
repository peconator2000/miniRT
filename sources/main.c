#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt	*data;
	t_figures	*figs;

	data = NULL;
	data = init();
	if (!parse(argc, argv, data) || !data)
		return (1);

	figs = data->scene->figs;
	while (figs)
	{
		if (figs->type == PLANE) {
			printf("PLANE: x = %f, y = %f, z = %f\nno_vec.x = %f, no_vec.y = %f, no_vec.z = %f\ncolor.r = %d, color.g = %d, color.b = %d",
					figs->fig.pl.coord.x, figs->fig.pl.coord.y, figs->fig.pl.coord.z, figs->no_vec.x, figs->no_vec.y, figs->no_vec.z, figs->color.r, figs->color.g, figs->color.b);
		} else if (figs->type == SPHERE) {
			printf("SPHERE: x = %f, y = %f, z = %f\ndiameter = %f\ncolor.r = %d, color.g = %d, color.b = %d",
					figs->fig.sp.coord.x, figs->fig.sp.coord.y, figs->fig.sp.coord.z, figs->fig.sp.diameter, figs->color.r, figs->color.g, figs->color.b);
		} else if (figs->type == CYLINDER) {
			printf("CYLINDER: x = %f, y = %f, z = %f\nno_vec.x = %f, no_vec.y = %f, no_vec.z = %f\ncolor.r = %d, color.g = %d color.b = %d\ndiameter = %f, height = %f\n",
					figs->fig.cy.coord.x, figs->fig.cy.coord.y, figs->fig.cy.coord.z, figs->no_vec.x, figs->no_vec.y, figs->no_vec.z, figs->color.r, figs->color.g, figs->color.b, figs->fig.cy.diameter, figs->fig.cy.height);
		}
		printf("\n\n");
		figs = figs->next;
	}

	controller(data);
	return (0);
}
