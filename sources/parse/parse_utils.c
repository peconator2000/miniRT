/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:04:12 by mwittenb          #+#    #+#             */
/*   Updated: 2022/03/14 18:59:37 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	str_to_int(char **str)
{
	int i;
	int	neg;

	i = 0;
	neg = 1;
	if (**str == '-' && *((*str)++))
		neg = -1;
	while (ft_isdigit(**str))
		i = i * 10 + (*((*str)++) - '0');
	skip_space(str);
	return (i * neg);
}

double	str_to_double(char **str)
{
	(void)str;
	return (0.0);
}

void	skip_space(char **str)
{
	while (**str == 32 || **str == 9)
		(*str)++;
}

void	check_range(double num, double min, double max, char *elem_name)
{
	if (num < min || num > max)
	{
		ft_putstr_fd(elem_name, 2);
		scene_error("parametr out of range");
	}
}
