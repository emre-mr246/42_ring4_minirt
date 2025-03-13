/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:35 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 08:46:35 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <math.h>

t_vector	*get_intersection(t_ray *ray, void *object, int obj_type)
{
	t_vector	*intersection;

	intersection = NULL;
	if (obj_type == SPHERE)
		intersection = intersect_sphere(*ray, *(t_sphere *)object);
	else if (obj_type == CYLINDER)
		intersection = intersect_cylinder(*ray, *(t_cylinder *)object);
	else if (obj_type == PLANE)
		intersection = intersect_plane(*ray, *(t_plane *)object);
	return (intersection);
}

static int	check_object_intersection(t_ray *ray, void *object, int obj_type,
		t_minirt *minirt)
{
	t_vector	*intersection;
	int			color;
	float		distance;

	color = 0;
	intersection = get_intersection(ray, object, obj_type);
	if (intersection)
	{
		distance = calculate_distance(ray->origin, intersection);
		if (obj_type == SPHERE)
			((t_sphere *)object)->distance = distance;
		else if (obj_type == CYLINDER)
			((t_cylinder *)object)->distance = distance;
		else if (obj_type == PLANE)
			((t_plane *)object)->distance = distance;
		if (obj_type == SPHERE)
			color = calculate_sphere_shade((t_sphere *)object, minirt,
					intersection);
		else if (obj_type == CYLINDER)
			color = calculate_cylinder_shade((t_cylinder *)object, minirt,
					intersection);
		else if (obj_type == PLANE)
			color = calculate_plane_shade((t_plane *)object, ray, minirt,
					intersection);
		free(intersection);
	}
	return (color);
}

int	check_intersection_and_distance(t_ray *ray, t_minirt *minirt, int i,
		float *distance)
{
	int	color;

	color = check_object_intersection(ray, minirt->scene->objects[i],
			minirt->scene->obj_tags[i], minirt);
	if (color != 0)
	{
		if (minirt->scene->obj_tags[i] == SPHERE)
			*distance = ((t_sphere *)minirt->scene->objects[i])->distance;
		else if (minirt->scene->obj_tags[i] == CYLINDER)
			*distance = ((t_cylinder *)minirt->scene->objects[i])->distance;
		else if (minirt->scene->obj_tags[i] == PLANE)
			*distance = ((t_plane *)minirt->scene->objects[i])->distance;
	}
	else
		*distance = INFINITY;
	return (color);
}
