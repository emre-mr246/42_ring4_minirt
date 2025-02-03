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

int	handle_keypress(int key, t_minirt *minirt)
{
    if (key == XK_Escape)
        ft_exit(NULL, 0, minirt);
	if (key == XK_w)
		minirt->scene->camera->pos->x += 0.1;
	if (key == XK_s)
		minirt->scene->camera->pos->x -= 0.1;
	if (key == XK_a)
		minirt->scene->camera->pos->z += 0.1;
	if (key == XK_d)
		minirt->scene->camera->pos->z -= 0.1;
	if (key == XK_Up)
		minirt->scene->camera->orientation->x += 0.005f;
	if (key == XK_Down)
		minirt->scene->camera->orientation->x -= 0.005f;
	if (key == XK_Left)
		minirt->scene->camera->orientation->z += 0.005f;
	if (key == XK_Right)
		minirt->scene->camera->orientation->z -= 0.005f;
	return (0);
}

int	handle_mouse(int x, int y, t_minirt *minirt)
{
	if (y != minirt->last_y)
	{
		if (y > minirt->last_y)
			minirt->scene->camera->pos->y -= 0.01;
		else
			minirt->scene->camera->pos->y += 0.01;
	}
	if (x != minirt->last_x)
	{
		if (x > minirt->last_x)
			minirt->scene->camera->pos->z -= 0.01;
		else
			minirt->scene->camera->pos->z += 0.01;
	}
	minirt->last_y = y;
	minirt->last_x = x;
    return (0);
}
