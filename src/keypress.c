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

void reset_camera(t_minirt *minirt)
{
	minirt->scene->camera->pos->x = 0;
	minirt->scene->camera->pos->y = 0;
	minirt->scene->camera->pos->z = 0;
	minirt->scene->camera->orientation->x = 1;
	minirt->scene->camera->orientation->y = 0;
	minirt->scene->camera->orientation->z = 0;
}

void move_camera_forward(t_minirt *minirt, t_vector *orientation, double move_step)
{
    minirt->scene->camera->pos->x += move_step * orientation->x;
    minirt->scene->camera->pos->y += move_step * orientation->y;
    minirt->scene->camera->pos->z += move_step * orientation->z;
}

void move_camera_sideways(t_minirt *minirt, t_vector *orientation, double move_step)
{
    minirt->scene->camera->pos->x -= move_step * orientation->z;
    minirt->scene->camera->pos->z += move_step * orientation->x;
}

int handle_keypress(int key, t_minirt *minirt)
{
	double move_step;;
	t_vector *orientation;

	move_step = 0.1;
	orientation = minirt->scene->camera->orientation;
	if (key == XK_Escape)
		ft_exit(NULL, 42, minirt);
	if (key == XK_w)
	    move_camera_forward(minirt, orientation, move_step);
	if (key == XK_s)
		move_camera_forward(minirt, orientation, -move_step);
	if (key == XK_a)
		move_camera_sideways(minirt, orientation, move_step);
	if (key == XK_d)
		move_camera_sideways(minirt, orientation, -move_step);
	if (key == XK_space)
		minirt->scene->camera->pos->y += move_step;
	if (key == XK_c)
		minirt->scene->camera->pos->y -= move_step;
	if (key == XK_r)
		reset_camera(minirt);
	// DEBUG AMAÇLI SİLİNECEK IŞIĞI HAREKET ETTİRİYOR
	if (key == XK_Up)
		minirt->scene->lights[0]->pos->x += move_step * 10;
	if (key == XK_Down)
		minirt->scene->lights[0]->pos->x -= move_step * 10;
	if (key == XK_Left)
		minirt->scene->lights[0]->pos->z += move_step * 10;
	if (key == XK_Right)
		minirt->scene->lights[0]->pos->z -= move_step * 10;
	if (key == XK_q)
		minirt->scene->lights[0]->pos->y += move_step * 10;
	if (key == XK_e)
		minirt->scene->lights[0]->pos->y -= move_step * 10;
	return (0);
}

int handle_mouse(int x, int y, t_minirt *minirt)
{
    static int last_x = -1;
    static int last_y = -1;

    if (last_x == -1 && last_y == -1)
    {
        last_x = x;
        last_y = y;
        return (0);
    }
    // if (y != last_y)
    //     minirt->scene->camera->orientation->x += 0.0015f * (last_y - y);
    if (x != last_x)
        minirt->scene->camera->orientation->z += 0.01f * (last_x - x);
    last_y = y;
    last_x = x;
    return (0);
}
