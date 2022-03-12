#include "miniRT.h"

int	parse(int argc, char **argv, t_minirt *minirt)
{
	char	*line;
	int		fd;

	(void)minirt;
	if (argc != 2)
		terminate("Usage ./miniRt *filename*.rt");
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		terminate("Can't open file");
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		// parse_element(line, )
		free(line);
		line = NULL;
	}
	free(line);
	return (1);
}
