/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:59:44 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 16:22:31 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H

# define STRUCTS_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	mix;
}				t_color;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}				t_point;

typedef struct s_vector
{
	t_point		start;
	t_point		end;
}				t_vector;

// Figures
typedef struct s_plane
{
	t_point		coord;
}				t_plane;

typedef struct s_sphere
{
	t_point		coord;
	t_point		newcoord;
	double		diameter;
	double		newdi;
}				t_sphere;

typedef struct s_cylinder
{
	t_point		coord;
	double		diameter;
	double		height;
	double		md;
}				t_cylinder;

typedef struct s_scene	t_scene;

union			u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
	t_scene		*scene;
};

typedef struct s_figures
{
	int					type;
	union u_figures		fig;
	t_color				color;
	t_point				no_vec;
	t_scene				*scene;
	t_point				r;
	t_point				u;
	t_point				d;
	int					in_dot;
	double				cy_t;
	int					is_check;
	struct s_figures	*next;
}				t_figures;

// Light
typedef struct s_light
{
	t_point		coord;
	t_point		newcoord;
	double		bri;
	t_color		color;
}				t_light;

// Camera
typedef struct s_camera
{
	t_point		pos;
	t_point		new_pos;
	t_point		no_vec;
	t_point		dir;
	t_point		rigth;
	t_point		up;
	int			deg;
	double		view_size[2];
}				t_camera;

// Scene
typedef struct s_scene
{
	int			resolution[2];
	t_camera	*camera;
	double		a_light;
	t_color		al_color;
	t_light		*light;
	t_figures	*figs;
}				t_scene;

typedef struct s_equ
{
	double	a;
	double	b;
	double	c;
	double	discr;
	double	t1;
	double	t2;
	double	t_min;
}				t_equ;

typedef struct s_ray
{
	t_point	op;
	t_point	o;
	t_point	p;
}				t_ray;

typedef struct s_kostyl
{
	t_color		min_color;
	t_figures	*fig;
	t_ray		ray;
	double		min_t;
}				t_kostyl;

#endif
