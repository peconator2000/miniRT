/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:14:13 by mwittenb          #+#    #+#             */
/*   Updated: 2022/03/15 15:47:04 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H

# define STRUCTS_H

typedef struct s_point3
{
	double	x;
	double	y;
	double	z;
}				t_point3;

typedef struct s_vector
{
	t_point3	start;
	t_point3	end;
}				t_vector;

// Figures
typedef struct s_plane
{
	t_point3	coord;
}				t_plane;

typedef struct s_sphere
{
	t_point3	coord;
	double		diameter;
}				t_sphere;

typedef struct s_cylinder
{
	t_point3	coord;
	double		diameter;
	double		height;
}				t_cylinder;

union			u_figures
{
	t_plane		pl;
	t_sphere	sp;
	t_cylinder	cy;
};

typedef struct s_figures
{
	int					type;
	union u_figures		fig;
	int					color;
	t_point3			no_vec;
	struct s_figures	*next;
}				t_figures;

// Light
typedef struct s_light
{
	t_point3	coord;
	double		brightness;
	int			color;
}				t_light;

// Camera
typedef struct s_camera
{
	t_point3	pos;
	t_point3	no_vec;
	int			degree;
}				t_camera;

// Scene
typedef struct s_scene
{
	int			resolution[2];
	t_camera	*camera;
	double		a_light;
	int			al_color;
	t_light		*light;
	t_figures	*figs;
}				t_scene;

#endif
