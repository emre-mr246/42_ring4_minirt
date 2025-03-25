/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:07:32 by emgul             #+#    #+#             */
/*   Updated: 2025/03/25 09:04:24 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "X11/keysym.h"
#include "minirt.h"
#include <math.h>

void	move_camera_forward(t_minirt *minirt, t_vector *orientation,
		double move_step)
{
	minirt->scene->camera->pos->x += move_step * orientation->x;
	minirt->scene->camera->pos->y += move_step * orientation->y;
	minirt->scene->camera->pos->z += move_step * orientation->z;
}

void	move_camera_sideways(t_minirt *minirt, t_vector *orientation,
		double move_step)
{
	minirt->scene->camera->pos->x -= move_step * orientation->z;
	minirt->scene->camera->pos->z += move_step * orientation->x;
}

void	rotate_camera(t_minirt *minirt, double y)
{
	t_vector	*orientation;

	orientation = minirt->scene->camera->orientation;
	orientation->x = orientation->x * cos(y) + orientation->z * sin(y);
	orientation->z = -orientation->x * sin(y) + orientation->z * cos(y);
	normalize_vector(orientation);
}

void	move_camera(int key, t_minirt *minirt)
{
	double		move_step;
	t_vector	*orientation;

	move_step = 0.5;
	orientation = minirt->scene->camera->orientation;
	if (key == XK_w)
		move_camera_forward(minirt, orientation, move_step);
	if (key == XK_s)
		move_camera_forward(minirt, orientation, -move_step);
	if (key == XK_a)
		move_camera_sideways(minirt, orientation, move_step);
	if (key == XK_d)
		move_camera_sideways(minirt, orientation, -move_step);
}

int	handle_keypress(int key, t_minirt *minirt)
{
	double	move_step;

	move_step = 0.5;
	if (key == XK_w || key == XK_s || key == XK_a || key == XK_d)
		move_camera(key, minirt);
	if (key == XK_Escape)
		ft_exit(NULL, 0, minirt);
	if (key == XK_space)
		minirt->scene->camera->pos->y += move_step;
	if (key == XK_c)
		minirt->scene->camera->pos->y -= move_step;
	if (key == XK_r)
		reset_camera(minirt);
	if (key == XK_q)
		rotate_camera(minirt, -0.1);
	if (key == XK_e)
		rotate_camera(minirt, 0.1);
	return (0);
}
