/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:27:49 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/07 20:27:49 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	count_figures(t_figures *first)
{
	int			size;
	t_figures	*curr_fig;

	if (!first)
		return (0);
	size = 1;
	curr_fig = first->next;
	while (curr_fig)
	{
		curr_fig = curr_fig->next;
		size++;
	}
	return (size);
}

t_figures	*new_figure(int type)
{
	t_figures	*figure;

	figure = (t_figures *)err_malloc(sizeof(t_figures));
	figure->type = type;
	figure->next = NULL;
	return (figure);
}

t_figures	*get_last_fig(t_figures *figs)
{
	t_figures	*last_fig;

	if (!figs)
		return (NULL);
	last_fig = figs;
	while (last_fig->next)
		last_fig = last_fig->next;
	return (last_fig);
}

void	add_figure(t_figures **head, t_figures *figure)
{
	t_figures	*last_fig;

	if (*head)
	{
		last_fig = get_last_fig(*head);
		last_fig->next = figure;
	}
	else
		*head = figure;
}

void	free_figures(t_figures *figures)
{
	t_figures	*tmp;

	while (figures)
	{
		tmp = figures->next;
		free(figures);
		figures = tmp;
	}
}
