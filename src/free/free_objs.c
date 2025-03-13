/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:28 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 08:46:29 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

void	free_camera(t_camera *camera)
{
	if (camera)
	{
		if (camera->pos)
			free(camera->pos);
		if (camera->orientation)
			free(camera->orientation);
		free(camera);
	}
}

void	free_light(t_light *light)
{
	if (light)
	{
		if (light->pos)
			free(light->pos);
		free(light);
	}
}

void	free_sphere(t_sphere *sphere)
{
	if (sphere)
	{
		if (sphere->origin)
			free(sphere->origin);
		free(sphere);
	}
}

void	free_plane(t_plane *plane)
{
	if (plane)
	{
		if (plane->point)
			free(plane->point);
		if (plane->normal)
			free(plane->normal);
		free(plane);
	}
}

void	free_cylinder(t_cylinder *cylinder)
{
	if (cylinder)
	{
		if (cylinder->origin)
			free(cylinder->origin);
		if (cylinder->axis)
			free(cylinder->axis);
		free(cylinder);
	}
}
