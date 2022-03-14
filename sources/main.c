#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt	*minirt;

	minirt = init();
	if (!parse(argc, argv, minirt))
		return (1);
	free_minirt(minirt);
	mlx_loop(minirt->mlx);
	return (0);
}
