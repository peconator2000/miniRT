/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:14:13 by mwittenb          #+#    #+#             */
/*   Updated: 2022/03/16 18:06:14 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H

# define STRUCTS_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
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
	double		diameter;
}				t_sphere;

typedef struct s_cylinder
{
	t_point		coord;
	double		diameter;
	double		height;
}				t_cylinder;

union			u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};

typedef struct s_figures
{
	int					type;
	union u_figures		fig;
	int					color;
	t_point				no_vec;
	struct s_figures	*next;
}				t_figures;

// Light
typedef struct s_light
{
	t_point		coord;
	double		brightness;
	int			color;
}				t_light;

// Camera
typedef struct s_camera
{
	t_point		pos;
	t_point		new_pos;//положение в новой системе координат
	t_point		no_vec;
	t_point		dir;	//z
	t_point		rigth;	//y
	t_point		up;		//x
	int			deg;
	double		view_size[2];//размеры окна просмотра новые
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
