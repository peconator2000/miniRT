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


// t_sphere	*sphere_init(void)
// {
// 	t_sphere	*sph;

// 	sph = malloc(sizeof(t_sphere));
// 	if (!sph)
// 		return (NULL);
// 	sph->rad = 100;
// 	sph->centre.x = 400;
// 	sph->centre.y = 600;
// 	sph->centre.z = 0;
// 	return (sph);
// }

// t_figures *init_sp()
// {
// 	t_figures *figs = err_malloc(sizeof(t_figures));
// 	figs->fig.sp.coord = parse_point3(ft_strdup(""));
// 	figs->fig.sp.diameter = 100;
// }

int	main(int argc, char **argv)
{
	t_minirt	*data;

	data = NULL;
	data = init();
	if (!parse(argc, argv, data) || !data)
		return (1);
	printf("data->img->addr: %p\n", data->img->addr);
	// data->scene->figs = init_sp();
	controller(data);
	return (0);
}
