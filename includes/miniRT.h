/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:14:21 by mwittenb          #+#    #+#             */
/*   Updated: 2022/03/15 22:58:49 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "colors.h"
# include "structs.h"

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_minirt
{
	void		*mlx; //init
	void		*win;
	t_image		*img;
	t_scene		*scene;
}				t_minirt;

// Parse
int			parse(int argc, char **argv, t_minirt *minirt);
t_minirt	*init();
void		init_mlx(t_minirt *minirt);

// Parse info
void		parse_resolution(t_minirt *minirt, char **str);
void		parse_ambient_light(t_minirt *minirt, char **str);
void		parse_light(t_minirt *minirt, char **str);
void		parse_camera(t_minirt *minirt, char **str);

// Parse figures
void		parse_cylinder(t_figures **figs, char **str);
void		parse_sphere(t_figures **figs, char **str);
void		parse_plane(t_figures **figs, char **str);

// Parse_utils
int			str_to_int(char **str);
double		str_to_double(char **str);
void		skip_space(char **str);
void		check_range(double num, double min, double max, char *elem_name);
void		comma(char **str);
int			parse_color(char **str);
t_point		parse_point3(char **str);

// Vector operations
double		get_dot(t_point point1, t_point point2);
double		get_module(t_point point1, t_point point2);
t_point		normalize(t_point point);

// Error handling
void		scene_error(char *msg);
void		terminate(char *msg);
void		*err_malloc(unsigned int size);

// Draw
int			draw_figures(t_minirt *data);
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);

// Control
void		controller(t_minirt *data);

// Utils
void		free_minirt(t_minirt *minirt);

#endif
