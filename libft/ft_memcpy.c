/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:10:42 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:10:46 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*to;
	unsigned const char	*from;

	if (dst == NULL && src == NULL && n != 0)
		return (NULL);
	to = (unsigned char *)dst;
	from = (unsigned char *)src;
	while (n--)
		*(to++) = *(from++);
	return (dst);
}
