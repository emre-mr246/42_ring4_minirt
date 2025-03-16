/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:52:30 by emgul             #+#    #+#             */
/*   Updated: 2025/03/16 15:45:57 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

static void	calculate_right_up_vectors(t_vector *orientation, t_vector **right,
		t_vector **up)
{
	t_vector	*world_up;

	world_up = init_vector(0, 1, 0);
	*right = cross_product(orientation, world_up);
	*up = cross_product(*right, orientation);
	free(world_up);
}

static t_vector	*get_ray_direction(t_viewport_coord *viewport_coord,
		t_vector *forward, t_vector **right, t_vector **up)
{
	t_vector	*dir;

	dir = init_vector(0, 0, 0);
	if (!dir)
		return (NULL);
	dir->x = forward->x + ((*right)->x * viewport_coord->x) + ((*up)->x
			* viewport_coord->y);
	dir->y = forward->y + ((*right)->y * viewport_coord->x) + ((*up)->y
			* viewport_coord->y);
	dir->z = forward->z + ((*right)->z * viewport_coord->x) + ((*up)->z
			* viewport_coord->y);
	return (dir);
}

void	calc_viewport_coord(int x, int y, t_minirt *mrt, t_viewport_coord *vc)
{
	t_viewport	*viewport;
	double		u;
	double		v;

	viewport = mrt->scene->viewport;
	u = (double)x / (WIN_W - 1);
	v = 1.0 - (double)y / (WIN_H - 1);
	vc->x = viewport->width * (u - 0.5);
	vc->y = viewport->height * (v - 0.5);
}

static t_vector	*calculate_ray_direction(int x, int y, t_minirt *minirt)
{
	t_vector			*right;
	t_vector			*up;
	t_vector			*dir;
	t_viewport_coord	*vc;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return (NULL);
	vc = (t_viewport_coord *)ft_calloc(sizeof(t_viewport_coord), 1);
	if (!vc)
		return (NULL);
	calc_viewport_coord(x, y, minirt, vc);
	calculate_right_up_vectors(minirt->scene->camera->orientation, &right, &up);
	dir = get_ray_direction(vc, minirt->scene->camera->orientation,
			&right, &up);
	normalize_vector(dir);
	if (vector_len(dir) < MIN_RENDER_DIST || vector_len(dir) > MAX_RENDER_DIST)
	{
		free(dir);
		dir = NULL;
	}
	free(vc);
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
