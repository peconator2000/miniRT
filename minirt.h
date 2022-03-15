#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "mlx/mlx.h"


typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_screen
{
	t_image *img;
	void	*init;
	void	*win;
	int		len;
	int		high;
}				t_screen;

typedef struct s_dot
{
	double		x;
	double		y;
	double		z;
}				t_dot;

typedef struct s_sphere
{
	double		rad;
	t_dot		centre;
	t_screen	*scr;
}				t_sphere;

typedef struct s_data
{
	t_screen	*scr;
	t_sphere	*sph;
	t_dot		*camera;
	t_dot		*ligth;
	t_dot		*basis;
}				t_data;

t_data	*data_init(void);
int		draw_figures(t_data *data);
void	controller(t_data *data);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	create_image(t_screen *scr);

#endif