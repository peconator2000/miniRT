/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:31:37 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:32:30 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	create_color(int red, int green, int blue)
{
	t_color	color;

	color.r = red;
	color.g = green;
	color.b = blue;
	color.mix = (red << 16) | (green << 8) | blue;
	return (color);
}

t_color	parse_color(char **str)
{
	int		red;
	int		green;
	int		blue;
	t_color	color;

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
	color = create_color(red, green, blue);
	return (color);
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
