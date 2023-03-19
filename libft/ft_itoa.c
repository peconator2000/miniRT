/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:11:34 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:11:34 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_size(int num)
{
	int	size;

	size = 1;
	if (num < 0)
	{
		num *= -1;
		size += 1;
	}
	while (num / 10)
	{
		size += 1;
		num /= 10;
	}
	return (size);
}

static void	ft_convert_to_str(char **dst, int start, int size, int n)
{
	int	i;
	int	degree;
	int	curr_num;

	i = start;
	while (size)
	{
		degree = ft_pow_recursive(10, size - 1);
		curr_num = (n / degree + '0');
		(*dst)[i] = (char)curr_num;
		n %= degree;
		i++;
		size--;
	}
	(*dst)[i] = '\0';
}

char	*ft_itoa(int n)
{
	int		i;
	int		size;
	char	*res;

	i = 0;
	if (n == -2147483648)
	{
		res = ft_strdup("-2147483648");
		return (res);
	}
	size = ft_count_size(n);
	res = (char *)malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		res[i] = '-';
		size--;
		i++;
	}
	ft_convert_to_str(&res, i, size, n);
	return (res);
}
