/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwittenb <mwittenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:33:01 by mwittenb          #+#    #+#             */
/*   Updated: 2022/04/08 16:36:02 by mwittenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_minirt(t_minirt *minirt)
{
	free_figures(minirt->scene->figs);
	free(minirt->scene->light);
	free(minirt->scene->camera);
	free(minirt->img);
	free(minirt->scene);
	free(minirt);
}
