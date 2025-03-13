/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:53:23 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 08:53:44 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_camera(t_minirt *minirt)
{
	minirt->scene->camera->pos->x = 0;
	minirt->scene->camera->pos->y = 0;
	minirt->scene->camera->pos->z = 0;
	minirt->scene->camera->orientation->x = 1;
	minirt->scene->camera->orientation->y = 0;
	minirt->scene->camera->orientation->z = 0;
}
