#include "miniRT.h"

void	free_minirt(t_minirt *minirt)
{
	free_figures(minirt->scene->figs);
	free(minirt->scene->light);
	free(minirt->scene->camera);
	free(minirt->img);
	free(minirt->scene);
	free(minirt);
}
