/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:13:02 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:13:02 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*duplicate_str;
	char	*start;
	char	*temp;
	char	*str1;

	str1 = (char *)s1;
	temp = str1;
	while (*temp)
		temp++;
	duplicate_str = (char *)malloc(sizeof(char) * (temp - str1 + 1));
	if (!duplicate_str)
		return (NULL);
	start = duplicate_str;
	while (*str1)
		*duplicate_str++ = *str1++;
	*duplicate_str = '\0';
	return (start);
}
