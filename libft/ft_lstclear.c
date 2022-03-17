/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:11:25 by mwittenb          #+#    #+#             */
/*   Updated: 2022/03/17 16:01:10 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp_el;

	if (lst)
	{
		while (*lst)
		{
			tmp_el = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp_el;
		}
	}
}
