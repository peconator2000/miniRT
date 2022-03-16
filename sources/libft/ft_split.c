/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:13:10 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:13:41 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **array)
{
	unsigned int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static int	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 1;
	words = 0;
	if (!s || !*s)
		return (0);
	if (s[0] != c)
		words++;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

static char	**ft_malloc_array(char const *str, char separate)
{
	char	**array;
	int		words;

	words = ft_count_words(str, separate);
	array = (char **)malloc(sizeof(*array) * (words + 1));
	if (!array)
		return (NULL);
	return (array);
}

static char	*ft_create_word(char const *s, char c, size_t *i)
{
	int		ind;
	int		size;
	char	*word;

	size = 0;
	ind = *i;
	while (s[ind] && s[ind] != c)
	{
		size++;
		ind++;
	}
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	ind = 0;
	while (s[*i] && s[*i] != c)
	{
		word[ind] = s[*i];
		(*i)++;
		ind++;
	}
	word[ind] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	s_size;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	array = ft_malloc_array(s, c);
	if (!(array))
		return (NULL);
	i = 0;
	j = 0;
	s_size = ft_strlen(s);
	while (i < s_size && s[i])
	{
		if (i < s_size && (char)s[i] != c)
		{
			array[j] = ft_create_word(s, c, &i);
			if (!array[j++])
				return (ft_malloc_error(array));
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}
