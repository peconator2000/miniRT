#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt	*minirt;

	minirt = init();
	if (!parse(argc, argv, minirt))
		return (1);
	free_minirt(minirt);
	// mlx_loop(minirt->mlx);
	controller(data);
	return (0);
}

int	main(void)
{
	t_data	*data;

	data = NULL;
	data = data_init();
	if (!data)
		return (0);
	controller(data);
	return (0);
}
