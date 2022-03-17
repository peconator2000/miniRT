#include "miniRT.h"

int	parse_color(char **str)
{
	int	red;
	int	green;
	int	blue;

	red = 0;
	green = 0;
	blue = 0;
	red = str_to_int(str);
	check_range(red, 0.0, 255, "COLOR");
	comma(str);
	green = str_to_int(str);
	check_range(green, 0.0, 255, "COLOR");
	comma(str);
	blue = str_to_int(str);
	check_range(blue, 0.0, 255, "COLOR");
	return ((red << 16) | (green << 8) | blue);
}

t_point	parse_point3(char **str)
{
	t_point	point;

	point.x = str_to_double(str);
	comma(str);
	point.y = str_to_double(str);
	comma(str);
	point.z = str_to_double(str);
	skip_space(str);
	return (point);
}
