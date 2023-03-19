/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:13:15 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:13:39 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_rank(int num)
{
	int	rank;

	rank = 1;
	while (num / 10)
	{
		rank *= 10;
		num /= 10;
	}
	return (rank);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	rank;
	int	num;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	rank = ft_count_rank(n);
	while (rank)
	{
		num = n / rank + '0';
		ft_putchar_fd(num, fd);
		n %= rank;
		rank /= 10;
	}
}
