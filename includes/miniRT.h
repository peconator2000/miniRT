/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:14:21 by mwittenb          #+#    #+#             */
/*   Updated: 2022/03/15 16:33:15 by mwittenb         ###   ########.fr       */
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
	void		*mlx;//init
	void		*win;
	t_image		*img;
	t_scene		*scene;
}				t_minirt;

// typedef struct s_image
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }			t_image;

// typedef struct s_screen
// {
// 	t_image *img;
// 	void	*init;
// 	void	*win;
// 	int		len;
// 	int		high;
// }				t_screen;

// typedef struct s_dot
// {
// 	double		x;
// 	double		y;
// 	double		z;
// }				t_dot;

// typedef struct s_sphere
// {
// 	double		rad;
// 	t_dot		centre;
// 	t_screen	*scr;
// }				t_sphere;

// typedef struct s_data
// {
// 	t_screen	*scr;
// 	t_sphere	*sph;
// 	t_dot		*camera;
// 	t_dot		*ligth;
// 	t_dot		*basis;
// }				t_data;

// Parse
int			parse(int argc, char **argv, t_minirt *minirt);
t_minirt	*init();
void		init_mlx(t_minirt *minirt, int choose);

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

// Error handling
void		scene_error(char *msg);
void		terminate(char *msg);
void		*err_malloc(unsigned int size);

// Utils
void		free_minirt(t_minirt *minirt);


//old fun
// t_data	*data_init(void);
int		draw_figures(t_minirt *data);
void	controller(t_minirt *data);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
// void	create_image(t_screen *scr);

#endif
