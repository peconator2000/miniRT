/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:12:57 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/04 14:20:54 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_clean(char ***obj)
{
	free(**obj);
	**obj = NULL;
}

static int	ft_write_in_line(char **remainder, char **line)
{
	int		length;
	char	*tmp;

	length = ft_cstrlen(*remainder, '\n');
	if ((*remainder)[length] == '\n')
	{
		*line = ft_substr(*remainder, 0, length);
		tmp = ft_strdup(&(*remainder)[length + 1]);
		free(*remainder);
		*remainder = tmp;
		if (!(*remainder) || !tmp)
			ft_clean(&remainder);
	}
	else if (*remainder)
	{
		*line = ft_strdup(*remainder);
		ft_clean(&remainder);
		return (0);
	}
	return (1);
}

static int	ft_return(char **line, char **remainder, int read_bytes)
{
	if ((*remainder) && ft_cstrlen(*remainder, 0) && read_bytes >= 0)
		return (ft_write_in_line(remainder, line));
	ft_clean(&remainder);
	if (read_bytes < 0)
		return (-1);
	if (!*line)
	{
		*line = ft_strdup("\0");
		if (!*line)
			return (-1);
	}
	return (0);
}

static int	ft_init_vars(char **buffer, char **remainder, int *read_bytes)
{
	*read_bytes = 1;
	*buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buffer)
		return (-1);
	*buffer[0] = '\0';
	if (!*remainder)
	{
		*remainder = ft_strdup(*buffer);
		if (!*remainder)
		{
			free(buffer);
			return (-1);
		}
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*remainder;
	char		*temp;
	char		*buffer;
	int			read_bytes;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line)
		return (-1);
	if (ft_init_vars(&buffer, &remainder, &read_bytes) == -1)
		return (-1);
	while (!is_newline(remainder) && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(remainder);
			free(buffer);
			return (-1);
		}
		buffer[read_bytes] = '\0';
		temp = ft_strjoin(remainder, buffer);
		free(remainder);
		remainder = temp;
	}
	free(buffer);
	return (ft_return(line, &remainder, read_bytes));
}
