/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:21 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 08:46:22 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

void	calculate_right_up_vectors(t_vector *orientation, t_vector **right,
		t_vector **up)
{
	t_vector	*world_up;

	world_up = init_vector(0, 1, 0);
	*right = cross_product(orientation, world_up);
	*up = cross_product(*right, orientation);
	free(world_up);
}

t_vector	*get_ray_direction(double viewport_x, double viewport_y,
		t_vector *forward, t_vector right, t_vector up)
{
	t_vector	*dir;

	dir = init_vector(0, 0, 0);
	if (!dir)
		return (NULL);
	dir->x = forward->x + (right.x * viewport_x) + (up.x * viewport_y);
	dir->y = forward->y + (right.y * viewport_x) + (up.y * viewport_y);
	dir->z = forward->z + (right.z * viewport_x) + (up.z * viewport_y);
	return (dir);
}

void	calculate_viewport_coordinates(int x, int y, t_minirt *minirt,
		double *viewport_x, double *viewport_y)
{
	t_viewport	*viewport;
	double		u;
	double		v;

	viewport = minirt->scene->viewport;
	u = (double)x / (WIN_W - 1);
	v = 1.0 - (double)y / (WIN_H - 1);
	*viewport_x = viewport->width * (u - 0.5);
	*viewport_y = viewport->height * (v - 0.5);
}

t_vector	*calculate_ray_direction(int x, int y, t_minirt *minirt)
{
	double		viewport_x;
	double		viewport_y;
	t_vector	*right;
	t_vector	*up;
	t_vector	*dir;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return (NULL);
	calculate_viewport_coordinates(x, y, minirt, &viewport_x, &viewport_y);
	calculate_right_up_vectors(minirt->scene->camera->orientation, &right, &up);
	dir = get_ray_direction(viewport_x, viewport_y,
			minirt->scene->camera->orientation, *right, *up);
	normalize_vector(dir);
	if (vector_length(dir) < MIN_RENDER_DISTANCE
		|| vector_length(dir) > MAX_RENDER_DISTANCE)
	{
		free(dir);
		dir = NULL;
	}
	free(right);
	free(up);
	return (dir);
}

t_ray	*send_ray_from_cam(int x, int y, t_minirt *minirt)
{
	t_vector	*direction;
	t_ray		*ray;

	direction = calculate_ray_direction(x, y, minirt);
	if (!direction)
		return (NULL);
	ray = init_ray(*minirt->scene->camera->pos, *direction);
	free(direction);
	return (ray);
}
