/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:13:33 by mwittenb          #+#    #+#             */
/*   Updated: 2022/02/26 15:13:34 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_el;
	t_list	*new_el;
	t_list	*temp_el;

	if (lst)
	{
		temp_el = lst;
		first_el = ft_lstnew(f(temp_el->content));
		if (!first_el)
			return (NULL);
		temp_el = temp_el->next;
		while (temp_el)
		{
			new_el = ft_lstnew(f(temp_el->content));
			if (!new_el)
			{
				ft_lstclear(&first_el, del);
				return (NULL);
			}
			ft_lstadd_back(&first_el, new_el);
			temp_el = temp_el->next;
		}
		return (first_el);
	}
	return (NULL);
}
