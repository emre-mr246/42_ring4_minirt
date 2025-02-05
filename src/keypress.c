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

int handle_keypress(int key, t_minirt *minirt)
{
	if (key == XK_Escape)
		ft_exit(NULL, 42, minirt);
	if (key == XK_w)
		minirt->scene->camera->pos->x += 0.1;
	if (key == XK_s)
		minirt->scene->camera->pos->x -= 0.1;
	if (key == XK_a)
		minirt->scene->camera->pos->z += 0.1;
	if (key == XK_d)
		minirt->scene->camera->pos->z -= 0.1;
	if (key == XK_space)
		minirt->scene->camera->pos->y += 0.1;
	if (key == XK_Control_L)
		minirt->scene->camera->pos->y -= 0.1;
	return (0);
}

int handle_mouse(int x, int y, t_minirt *minirt)
{
	static unsigned int last_y;
	static unsigned int last_x;

	if (y != last_y)
	{
		if (y > last_y)
			minirt->scene->camera->orientation->x -= 0.001f;
		else
			minirt->scene->camera->orientation->x += 0.001f;
	}
	if (x != last_x)
	{
		if (x > last_x)
			minirt->scene->camera->orientation->z -= 0.001f;
		else
			minirt->scene->camera->orientation->z += 0.001f;
	}
	last_y = y;
	last_x = x;
	return (0);
}
