/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:14:41 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:16:08 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	scene_error(char *msg)
{
	ft_putstr_fd("Scene error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

void	terminate(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	perror(msg);
	exit(1);
}

void	*err_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		terminate("Can't allocate memory");
	return (ptr);
}
