/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:12:11 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:12:11 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t		len;
	uint32_t	x;

	len = 0;
	while (1)
	{
		x = *((uint32_t *)str);
		if (!(x & 0x000000FF))
			return (len);
		if (!(x & 0x0000FF00))
			return (len + 1);
		if (!(x & 0x00FF0000))
			return (len + 2);
		if (!(x & 0xFF000000))
			return (len + 3);
		len += 4;
		str += 4;
	}
}
