/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cstrlen_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:23:03 by mwittenb          #+#    #+#             */
/*   Updated: 2022/03/11 16:15:56 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_cstrlen(const char *str, char c)
{
	char	*copy_str;

	copy_str = (char *)str;
	while (*copy_str && *copy_str != c)
		copy_str++;
	return (copy_str - str);
}
