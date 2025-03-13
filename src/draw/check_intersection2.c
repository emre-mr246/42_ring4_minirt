/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:34 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 08:46:34 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <math.h>

static int	find_closest_intersection(t_minirt *minirt, int *colors,
		float *distances)
{
	int		i;
	int		closest_index;
	float	min_distance;

	closest_index = -1;
	min_distance = INFINITY;
	i = 0;
	while (minirt->scene->objects[i])
	{
		if (colors[i] != 0)
		{
			if (distances[i] < min_distance)
			{
				min_distance = distances[i];
				closest_index = i;
			}
		}
		i++;
	}
	if (closest_index == -1)
		return (0);
	return (colors[closest_index]);
}

int	*check_object_colors(t_ray *ray, t_minirt *minirt, float *distances)
{
	int	i;
	int	color;
	int	*colors;

	colors = ft_calloc(minirt->scene->object_count, sizeof(int));
	if (!colors)
		return (NULL);
	i = 0;
	while (minirt->scene->objects[i])
	{
		color = check_intersection_and_distance(ray, minirt, i, &distances[i]);
		colors[i] = color;
		i++;
	}
	return (colors);
}

int	check_intersections(t_ray *ray, t_minirt *minirt)
{
	int		*colors;
	float	*distances;
	int		result;

	distances = ft_calloc(minirt->scene->object_count, sizeof(float));
	if (!distances)
		return (0);
	colors = check_object_colors(ray, minirt, distances);
	if (!colors)
	{
		free(distances);
		return (0);
	}
	result = find_closest_intersection(minirt, colors, distances);
	free(colors);
	free(distances);
	return (result);
}
