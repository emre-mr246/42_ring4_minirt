/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:07:32 by emgul             #+#    #+#             */
/*   Updated: 2024/10/17 16:16:46 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>
#include "X11/keysym.h"
#include <X11/X.h>

#include <math.h>

int handle_keypress(int key, t_minirt *minirt)
{
	double move_step;;
	t_vector *orientation;

	move_step = 0.1;
	orientation = minirt->scene->camera->orientation;
	if (key == XK_Escape)
		ft_exit(NULL, 42, minirt);
	if (key == XK_w)
	{
		minirt->scene->camera->pos->x += move_step * orientation->x;
		minirt->scene->camera->pos->y += move_step * orientation->y;
		minirt->scene->camera->pos->z += move_step * orientation->z;
	}
	if (key == XK_s)
	{
		minirt->scene->camera->pos->x -= move_step * orientation->x;
		minirt->scene->camera->pos->y -= move_step * orientation->y;
		minirt->scene->camera->pos->z -= move_step * orientation->z;
	}
	if (key == XK_a)
	{
		minirt->scene->camera->pos->x -= move_step * orientation->z;
		minirt->scene->camera->pos->z += move_step * orientation->x;
	}
	if (key == XK_d)
	{
		minirt->scene->camera->pos->x += move_step * orientation->z;
		minirt->scene->camera->pos->z -= move_step * orientation->x;
	}
	if (key == XK_space)
		minirt->scene->camera->pos->y += move_step;
	if (key == XK_Control_L)
		minirt->scene->camera->pos->y -= move_step;
	return (0);
}

int handle_mouse(int x, int y, t_minirt *minirt)
{
	static unsigned int last_y;
	static unsigned int last_x;

	if (y != last_y)
	{
		if (y > last_y)
			minirt->scene->camera->orientation->x -= 0.0005f * (y - last_y);
		else
			minirt->scene->camera->orientation->x += 0.0005f * (last_y - y);
	}
	if (x != last_x)
	{
		if (x > last_x)
			minirt->scene->camera->orientation->z -= 0.0005f * (x - last_x);
		else
			minirt->scene->camera->orientation->z += 0.0005f * (last_x - x);
	}
	last_y = y;
	last_x = x;
	return (0);
}
