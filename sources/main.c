#include "miniRT.h"

int	main(int argc, char **argv)
{
	(void)argv;

	char	*line;
	int		fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		return (1);
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	free(line);
	return (0);
}
