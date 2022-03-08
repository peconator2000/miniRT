/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_recursive_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:10:21 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:10:22 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow_recursive(int basis, int exponent)
{
	if (basis == 0)
		return (1);
	else if (exponent == 1)
		return (basis);
	else if (exponent % 2 == 0)
		return (ft_pow_recursive(basis * basis, exponent / 2));
	else
		return (ft_pow_recursive(basis * basis, exponent / 2) * basis);
}
