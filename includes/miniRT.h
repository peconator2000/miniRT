/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:59:06 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 16:35:15 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "structs.h"

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define PLANE		1
# define SPHERE		2
# define CYLINDER	3
# define STEP		2
# define EPSILON	0.0001

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
	void		*mlx;
	void		*win;
	t_image		*img;
	t_scene		*scene;
}				t_minirt;

// Parse
int			parse(int argc, char **argv, t_minirt *minirt);
t_minirt	*init(void);
void		init_mlx(t_minirt *minirt);

// Parse info
void		parse_resolution(t_minirt *minirt, char **str);
void		parse_ambient_light(t_minirt *minirt, char **str);
void		parse_light(t_minirt *minirt, char **str);
void		parse_camera(t_minirt *minirt, char **str);

// Parse figures
void		parse_cylinder(t_figures **figs, char **str, t_scene *scene);
void		parse_sphere(t_figures **figs, char **str, t_scene *scene);
void		parse_plane(t_figures **figs, char **str, t_scene *scene);

// Parse_utils
int			str_to_int(char **str);
double		str_to_double(char **str);
void		skip_space(char **str);
void		check_range(double num, double min, double max, char *elem_name);
void		comma(char **str);
t_color		create_color(int red, int green, int blue);
t_color		parse_color(char **str);
t_point		parse_point3(char **str);

// Figures utils
int			count_figures(t_figures *first);
t_figures	*new_figure(int type);
t_figures	*get_last_fig(t_figures *figs);
void		add_figure(t_figures **head, t_figures *figure);
void		free_figures(t_figures *figures);

// Vector operations
double		get_distance(t_point start, t_point end);
double		get_dot(t_point start, t_point end);
double		get_module(t_point start, t_point end);
t_point		normalize(t_point point);
void		normalize2(t_point *dot, t_point point);
t_point		point_define(double x, double y, double z);
t_point		vector_add(t_point start, t_point end);
t_point		vector_subtract(t_point start, t_point end);
t_point		vector_cross(t_point start, t_point end);
t_point		vector_nmultiply(t_point p1, double n);
double		vcos(t_point a, t_point b);
double		vsin(t_point a, t_point b);
t_point		vec_mult_coef(t_point vector, double coef);
t_point		reflect_ray(t_point ray, t_point normal);

// Error handling
void		scene_error(char *msg);
void		terminate(char *msg);
void		*err_malloc(unsigned int size);

// Color
void		add_coeficient(double (*rgb)[3], double coef, int color);
t_color		build_color(int color, double rgb[3]);
void		fill_color(t_color *col, int r, int g, int b);
void		get_cy_coord(t_figures *fig, t_point *dot);
t_color		compute_cy_color(t_scene *sc, t_figures *fig,
				t_point dot, t_point norm);
t_color		compute_color(t_scene *scene, t_figures *figure,
				t_point ray, t_point dot);
int			check_shadow(t_scene *scene, t_point intersect, t_figures *figure);
void		show_type(t_figures *fig, char *str);
t_point		get_normal(t_figures *figure, t_point intersect, t_point ray);

// Control
int			key_hook(int keycode, t_minirt *data);
int			cross_icon(t_minirt *data);

// Coordinates
void		vec_equal(t_point *dot1, t_point *dot2);
void		vec_fill(t_point *res, double x, double y, double z);
void		vec_mult_vec(t_point *res, t_point a, t_point b);
void		vec_mult_num(t_point *res, double num);
double		vec_scalar_mult(t_point vec1, t_point vec2);

// Draw
void		draw_all(t_minirt *data, int wid, int hig);
int			draw_figures(t_minirt *data);
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);
void		controller(t_minirt *data);

// New Basis
void		get_norm(t_point *dot);
void		get_d(t_camera *cam);
void		get_r(t_camera *cam);
void		new_basis(t_scene *scene);
void		get_new_sizes(t_scene *sc, double *delta);
void		get_inscreen(t_scene *sc, t_point *dot, double x, double y);
void		get_new_coords(t_camera *cam, t_point *dot);

// Rays
int			get_color(t_minirt *data, double x_sc, double y_sc);
void		get_minimal_color(t_minirt *data, t_point dot, t_color *color);
void		cylinder_processing(t_kostyl *ko, t_scene *scene, t_point dot);
void		plane_processing(t_kostyl *ko, t_scene *scene);
void		sphere_processing(t_kostyl *ko, t_scene *scene);

double		is_cy_sphere(t_ray ray, t_figures *sp, t_point k, double md);
double		is_sphere(t_ray ray, t_figures *sp, double md);
void		ray_fill(t_ray *res, t_point o, t_point p);
void		get_ray_dot(t_point *res_dot, t_ray ray, double t_min);
int			is_valid_param(t_equ *equ, double md);

double		is_cy_plane(t_ray ray, t_figures *pl, t_point k);
double		is_plane(t_ray ray, t_figures *pl);
double		get_pl_t(t_point n, t_ray ray, t_point k);

double		is_cylinder(t_point o, t_point p, t_figures *cy, double md);
double		get_cy_t(t_equ equ, t_ray new_ray, t_figures *cy, t_ray ray);
void		in_dot_checker(t_figures *cy, t_ray new_ray, double hei);
int			is_valid_cy_param(t_equ *equ, double ed);
int			rem_cylinder(t_ray ray, double t_min, double hei);
void		swap_t(t_equ *equ);
void		back_world_basis(t_point *dot, t_figures *fig);
void		get_cy_basis_dot(t_point dot, t_point *new,
				t_figures *fig, t_point k);
double		get_matrix_determinant(t_point r, t_point u, t_point d);
void		get_new_cylinder_basis(t_figures *cy);
void		show_vec(char *str, t_point vec);

void		cy_normal(t_point *normal, t_point cy_coord);

// Vector operations
void		normalize2(t_point *dot, t_point point);
t_point		normalize(t_point point);
double		get_module(t_point start, t_point end);
double		get_dot(t_point start, t_point end);
double		get_distance(t_point start, t_point end);

// Utils
void		free_minirt(t_minirt *minirt);

#endif
