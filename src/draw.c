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

void fill_image(int size_x, int size_y, t_img *img, t_minirt *minirt)
{
	int x;
	int y;
	int pix;
	int color;

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

int draw(t_minirt *minirt)
{
	fill_image(minirt->win_width, minirt->win_height, &(minirt->img), minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img.ptr, 0, 0);
	return (1);
}

int check_sphere_intersection(t_ray *ray, t_minirt *minirt)
{
    int i;
    t_sphere *sp;
    t_vector *intersection;

    i = 0;
    while (minirt->scene->objects[i])
    {
        if (minirt->scene->obj_tags[i] == SPHERE)
        {
            sp = (t_sphere *)minirt->scene->objects[i];
			intersection = intersect_sphere(*ray, *sp);
            if (intersection)
            {
				free(intersection);
                return (sp->color);
            }
        }
        i++;
    }
    return 0;
}

void free_ray(t_ray *ray)
{
	if (ray->direction)
		free(ray->direction);
	if (ray->origin)
		free(ray->origin);
	if (ray)
		free(ray);
}

int clamp_color_value(int value)
{
	if (value > 255)
		return (255);
	if (value < 0)
		return (0);
	return (value);
}

int calculate_ambient_light(int color, t_amb_light *amb_light)
{
	int r;
	int g;
	int b;

	if (!amb_light)
		return (color);
	r = ((color >> 16) & 0xFF) * amb_light->intensity;
	g = ((color >> 8) & 0xFF) * amb_light->intensity;
	b = (color & 0xFF) * amb_light->intensity;
	r = clamp_color_value(r);
	g = clamp_color_value(g);
	b = clamp_color_value(b);
	return ((r << 16) | (g << 8) | b);
}

int get_color(int x, int y, t_minirt *minirt)
{
	t_ray *ray;
	int color;

	color = 0;
	ray = send_ray_from_cam(x, y, minirt);
	color = check_sphere_intersection(ray, minirt);
	color = calculate_ambient_light(color, minirt->scene->amb_light);
	free_ray(ray);
	return (color);
}
