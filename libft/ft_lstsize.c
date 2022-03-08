/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:11:17 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:11:17 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*curr_el;

	if (!lst)
		return (0);
	size = 1;
	curr_el = lst->next;
	while (curr_el)
	{
		curr_el = curr_el->next;
		size++;
	}
	return (size);
}
