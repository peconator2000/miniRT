#include "miniRT.h"

int	parse_color(char **str)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	(void)str;
	return (1);
}

t_point3	parse_point3(char **str)
{
	t_point3	point;

	(void)str;
	point.x = str_to_double(str);
	comma(str);
	point.y = str_to_double(str);
	comma(str);
	point.z = str_to_double(str);
	skip_space(str);
	return (point);
}
