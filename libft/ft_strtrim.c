/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:12:06 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:12:06 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_count_boders(char const *s1, char const *set,
							size_t *start, size_t *end)
{
	int	i;

	i = 0;
	while (set[i] && s1[*start])
	{
		if (s1[*start] == set[i])
		{
			i = -1;
			(*start)++;
		}
		i++;
	}
	i = 0;
	while (set[i] && s1[*start])
	{
		if (s1[*end] == set[i])
		{
			i = -1;
			(*end)--;
		}
		i++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	ft_count_boders(s1, set, &start, &end);
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	while (start <= end && s1[start])
	{
		str[i] = s1[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
