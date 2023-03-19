/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:12:04 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:12:05 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*little;
	char	*big;
	size_t	n_size;
	size_t	i;
	size_t	j;

	i = 0;
	n_size = ft_strlen(needle);
	little = (char *)needle;
	big = (char *)haystack;
	if (*little == 0)
		return ((char *)haystack);
	while (len > i && big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && len > (i + j))
		{
			if (j == (n_size - 1))
				return (big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
