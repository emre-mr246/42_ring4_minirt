/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:12:19 by emgul             #+#    #+#             */
/*   Updated: 2024/10/18 12:25:22 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

void	fill_image(int size_x, int size_y, t_img *img, t_minirt *minirt)
{
	int	x;
	int	y;
	int	pix;
	int	color;

	x = 0;
	while (x < size_x)
	{
		y = 0;
		while (y < size_y)
		{
			pix = (x * (img->bits_per_pixel / 8)) + (y * img->line_len);
			color = get_color(x, y, minirt);
		    img->data[pix] = color & 0xFF;
			img->data[pix + 1] = (color >> 8) & 0xFF;
			img->data[pix + 2] = (color >> 16) & 0xFF;
			y++;
		}
		x++;
	}
}
void	draw(t_minirt *minirt)
{
	fill_image(minirt->win_width, minirt->win_height, &(minirt->img), minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img.ptr, 0, 0);
}


void	*check_sphere_intersection(t_ray *ray, t_minirt *minirt)
{
	int i;
	t_vector *intersection;
	void *obj;

	i = 0;
	while (minirt->scene->objects[i])
	{
		if (minirt->scene->obj_tags[i] == SPHERE)
		{
			intersection = intersect_sphere(*ray, *(t_sphere *)minirt->scene->objects[i]);
			obj = minirt->scene->objects[i];
		}
		i++;
	}
	if (intersection)
		return (obj);
	return (NULL);
}

int	get_color(int x, int y, t_minirt *minirt)
{
	t_ray *ray;
    t_sphere *sp;

	ray = send_ray_from_cam(x, y, minirt);
    sp = (t_sphere *)check_sphere_intersection(ray, minirt);
	if (sp)
		return (sp->color);
	else
		return (0x000000);
}