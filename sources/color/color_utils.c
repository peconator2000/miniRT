/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:47 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 23:26:06 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	add_coeficient(double (*rgb)[3], double coef, int color)
{
	unsigned int	mask;

	if (coef < 0)
		return ;
	mask = 255 << 16;
	(*rgb)[0] += coef * ((color & mask) >> 16) * pow(255, -1);
	mask >>= 8;
	(*rgb)[1] += coef * ((color & mask) >> 8) * pow(255, -1);
	mask >>= 8;
	(*rgb)[2] += coef * (color & mask) * pow(255, -1);
}

t_color	build_color(int color, double rgb[3])
{
	unsigned int	mask;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	mask = 255 << 16;
	r = rgb[0] * ((color & mask) >> 16);
	mask >>= 8;
	g = rgb[1] * ((color & mask) >> 8);
	mask >>= 8;
	b = rgb[2] * (color & mask);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (create_color(r, g, b));
}

void	fill_color(t_color *col, int r, int g, int b)
{
	(*col).r = r;
	(*col).g = g;
	(*col).b = b;
	(*col).mix = (((*col).r << 16) | ((*col).g << 8) | (*col).b);
}
