/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:49:10 by vellie            #+#    #+#             */
/*   Updated: 2022/04/08 16:35:16 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	draw_all(t_minirt *data, int wid, int hig)
{
	int		x_pix;
	int		y_pix;
	double	x_sc;
	double	y_sc;

	y_pix = 0;
	y_sc = hig * (0.5);
	new_basis(data->scene);
	while (y_pix < hig)
	{
		x_pix = 0;
		x_sc = wid * (-0.5);
		while (x_pix < wid)
		{
			my_mlx_pixel_put(data->img, x_pix, y_pix,
				get_color(data, x_sc, y_sc));
			x_pix += 1;
			x_sc += 1;
		}
		y_pix += 1;
		y_sc -= 1;
	}
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	int		offset;
	char	*c;

	offset = (y * img->line_length) + (x * img->bits_per_pixel / 8);
	c = img->addr + offset;
	*(unsigned int *)c = color;
}

int	draw_figures(t_minirt *data)
{
	int	wid;
	int	hig;

	wid = data->scene->resolution[0];
	hig = data->scene->resolution[1];
	draw_all(data, wid, hig);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (1);
}

void	controller(t_minirt *data)
{
	draw_figures(data);
	mlx_hook(data->win, 17, 0, &cross_icon, (void *)data);
	mlx_key_hook(data->win, &key_hook, (void *)data);
	mlx_loop(data->mlx);
}
