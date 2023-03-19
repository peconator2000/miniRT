/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:12:10 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:12:10 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*f_str;

	i = 0;
	if (!s)
		return (NULL);
	f_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!f_str)
		return (NULL);
	while (s[i])
	{
		f_str[i] = f(i, s[i]);
		i++;
	}
	f_str[i] = '\0';
	return (f_str);
}
