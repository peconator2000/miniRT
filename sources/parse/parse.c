#include "miniRT.h"

static void	parse_line(t_minirt *minirt, t_figures **figs, char **strptr)
{
	char *str;

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
		parse_cylinder(figs, &str);
	else if (*str == 's' && *(str + 1) == 'p' && *(str++) && *(str)++)
		parse_sphere(figs, &str);
	else if (*str == 'p' && *(str + 1) == 'l' && *(str++) && *(str)++)
		parse_plane(figs, &str);
	*strptr = str;
}

static void	parse_element(t_minirt *minirt, t_figures **figs, char *line)
{
	while (*line)
	{
		parse_line(minirt, figs, &line);
		line++;
	}
}

int	parse(int argc, char **argv, t_minirt *minirt)
{
	char		*line;
	int			fd;
	t_figures	*figs;

	figs = minirt->scene->figs;
	if (argc != 2)
		terminate("Usage ./miniRt *filename*.rt");
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		terminate("Can't open file");
	while (get_next_line(fd, &line) > 0)
	{
		parse_element(minirt, &figs, line);
		free(line);
		line = NULL;
	}
	close(fd);
	free(line);
	return (1);
}
