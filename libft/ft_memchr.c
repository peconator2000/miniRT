/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:11:13 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:11:14 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	symbol;

	src = (unsigned char *)s;
	symbol = c;
	while (n--)
	{
		if (symbol == *(src))
			return (src);
		src++;
	}
	return (NULL);
}
