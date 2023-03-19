/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:30:01 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:30:15 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	parse_line(t_minirt *minirt, t_figures **figs, char **strptr)
{
	char	*str;

	str = *strptr;
	if (*str == 'R' && *(str++))
		parse_resolution(minirt, &str);
	else if (*str == 'A' && *(str++))
		parse_ambient_light(minirt, &str);
	else if (*str == 'C' && *(str++))
		parse_camera(minirt, &str);
	else if (*str == 'L' && *(str++))
		parse_light(minirt, &str);
	else if (*str == 'c' && *(str + 1) == 'y' && *(str++) && *(str)++)
		parse_cylinder(figs, &str, minirt->scene);
	else if (*str == 's' && *(str + 1) == 'p' && *(str++) && *(str)++)
		parse_sphere(figs, &str, minirt->scene);
	else if (*str == 'p' && *(str + 1) == 'l' && *(str++) && *(str)++)
		parse_plane(figs, &str, minirt->scene);
	*strptr = str;
}

static void	parse_element(t_minirt *minirt, t_figures **figs, char *line)
{
	if (*line)
		parse_line(minirt, figs, &line);
}

static void	read_file(t_minirt *minirt, t_figures **figs, int fd)
{
	char		*line;
	int			read_status;

	*figs = minirt->scene->figs;
	read_status = -1;
	read_status = get_next_line(fd, &line);
	if (read_status == -1)
		terminate("Can't open");
	while (read_status > 0)
	{
		parse_element(minirt, figs, line);
		free(line);
		line = NULL;
		read_status = get_next_line(fd, &line);
	}
	if (line)
	{
		parse_element(minirt, figs, line);
		free(line);
		line = NULL;
	}
	minirt->scene->figs = *figs;
}

int	parse(int argc, char **argv, t_minirt *minirt)
{
	int			fd;
	int			read_status;
	t_figures	*figs;

	figs = minirt->scene->figs;
	read_status = -1;
	if (argc != 2)
		terminate("Usage ./miniRt *filename*.rt");
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		terminate("Can't open file");
	read_file(minirt, &figs, fd);
	close(fd);
	return (1);
}
