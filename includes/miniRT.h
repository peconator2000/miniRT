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

# define PLANE		1
# define SPHERE		2
# define CYLINDER	3

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
t_point		point_define(double x, double y, double z);
t_point		vector_add(t_point start, t_point end);
t_point		vector_substract(t_point start, t_point end);
t_point		vector_cross(t_point start, t_point end);

// Error handling
void		scene_error(char *msg);
void		terminate(char *msg);
void		*err_malloc(unsigned int size);

// Draw
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);

// Control
void		controller(t_minirt *data);


int		draw_figures(t_minirt *data);
void	controller(t_minirt *data);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	create_image(t_minirt *data);

// Utils
void		free_minirt(t_minirt *minirt);

//coordinates_transformation
void	get_scene_point(t_point *res, t_scene *scene, int x, int y);//в res помещаем точку из экрана обзора
void	get_new_basis(t_scene *scene);

//vector_moves
void	vec_equal(t_point *dot1, t_point *dot2);
void	vec_fill(t_point *dot, double x, double y, double z);
void	vec_mult_vec(t_point *res, t_point vec1, t_point vec2);
void	vec_mult_num(t_point *res, double num);

//coordinats_transformations2
void delta_generate(double *delta_x, double *delta_y, t_scene *scene);

//get_color
int get_color(t_minirt *data, t_point dot);

//ray_tracing
void	sphere_ray(double *min_t, int *min_color, t_point dot, t_figures *elem);
void	new_camera_coords(t_point *dot, t_point old, t_camera *cam);
void	new_basis_coordinates(t_point *dot, t_point old, t_camera *cam);

//equations
double	get_discr_sp(t_point cen, t_point ve, double rad);


#endif
