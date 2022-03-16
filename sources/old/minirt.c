#include "minirt.h"

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