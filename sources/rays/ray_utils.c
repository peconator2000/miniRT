#include "miniRT.h"

void	cy_normal(t_point *normal, t_point cy_coord)
{
	(*normal).x -= cy_coord.x;
	(*normal).y -= cy_coord.y;
	(*normal).z -= cy_coord.z;
}
