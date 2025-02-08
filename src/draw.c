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
	return (create_rgb(r, g, b));
}

int is_in_shadow(t_vector *point, t_light *light, t_minirt *minirt)
{
	t_ray shadow_ray;
	t_vector direction;
	int i;

	direction.x = light->pos->x - point->x;
	direction.y = light->pos->y - point->y;
	direction.z = light->pos->z - point->z;
	normalize_vector(&direction);
	shadow_ray.origin = point;
	shadow_ray.direction = &direction;
	i = 0;
	while (minirt->scene->objects[i])
	{
		if (minirt->scene->obj_tags[i] == SPHERE)
		{
			if (intersect_sphere(shadow_ray, *(t_sphere *)minirt->scene->objects[i]))
				return (1);
		}
		else if (minirt->scene->obj_tags[i] == PLANE)
		{
			if (intersect_plane(shadow_ray, *(t_plane *)minirt->scene->objects[i]))
				return (1);
		}
		else if (minirt->scene->obj_tags[i] == CYLINDER)
		{
			if (intersect_cylinder(shadow_ray, *(t_cylinder *)minirt->scene->objects[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

float calculate_light_intensity(float intensity, t_vector *intersection, t_vector *normal, t_minirt *minirt, t_light *light)
{
	t_vector *light_dir;
	float dot;

	light_dir = subtract_vector(*light->pos, *intersection);
	normalize_vector(light_dir);
	dot = dot_product(*normal, *light_dir);
	if (dot > 0)
	{
		if (is_in_shadow(intersection, light, minirt))
			intensity += light->intensity * dot;
	}
	free(light_dir);
	return (fmin(fmax(intensity, minirt->scene->amb_light->intensity), 1.0));
}

int calculate_sphere_shade(t_sphere *sp, t_ray *ray, t_minirt *minirt, t_vector *intersection)
{
	t_vector *normal;
	float intensity;
	t_color color;
	int i;

	normal = subtract_vector(*intersection, *sp->origin);
	normalize_vector(normal);
	intensity = 0.1;
	i = 0;
	while (minirt->scene->lights[i])
	{
		intensity = calculate_light_intensity(intensity, intersection, normal, minirt, (t_light *)minirt->scene->lights[i]);
		i++;
	}
	color.r = clamp_color_value(((sp->color >> 16) & 0xFF) * intensity);
	color.g = clamp_color_value(((sp->color >> 8) & 0xFF) * intensity);
	color.b = clamp_color_value((sp->color & 0xFF) * intensity);
	free(normal);
	return (create_rgb(color.r, color.g, color.b));
}

int check_sphere_intersection(t_ray *ray, t_minirt *minirt)
{
	int i;
	t_sphere *sp;
	t_vector *intersection;
	int color;

	i = 0;
	color = 0;
	while (minirt->scene->objects[i])
	{
		if (minirt->scene->obj_tags[i] == SPHERE)
		{
			sp = (t_sphere *)minirt->scene->objects[i];
			intersection = intersect_sphere(*ray, *sp);
			if (intersection)
			{
				color = calculate_sphere_shade(sp, ray, minirt, intersection);
				free(intersection);
				return (color);
			}
		}
		i++;
	}
	return (0);
}

int check_plane_intersection(t_ray *ray, t_minirt *minirt)
{
	int i;
	t_plane *pl;
	t_vector *intersection;

	i = 0;
	while (minirt->scene->objects[i])
	{
		if (minirt->scene->obj_tags[i] == PLANE)
		{
			pl = (t_plane *)minirt->scene->objects[i];
			intersection = intersect_plane(*ray, *pl);
			if (intersection)
			{
				free(intersection);
				return (pl->color);
			}
		}
		i++;
	}
	return (0);
}

int check_cylinder_intersection(t_ray *ray, t_minirt *minirt)
{
	int i;
	t_cylinder *cylinder;
	t_vector *intersection;

	i = 0;
	while (minirt->scene->objects[i])
	{
		if (minirt->scene->obj_tags[i] == CYLINDER)
		{
			cylinder = (t_cylinder *)minirt->scene->objects[i];
			intersection = intersect_cylinder(*ray, *cylinder);
			if (intersection)
			{
				free(intersection);
				return (cylinder->color);
			}
		}
		// ışığı küre şeklinde görmek için debug amaçlı
		if (minirt->scene->obj_tags[i] == LIGHT)
		{
			t_sphere *sp;
			sp = malloc(sizeof(t_sphere));
			sp->origin = minirt->scene->lights[0]->pos;
			sp->radius = 0.5;
			sp->color = 0xFF0000;
			if (intersect_sphere(*ray, *sp))
				return (1);
			free(sp);
		}
		i++;
	}
	return (0);
}

int check_intersections(t_ray *ray, t_minirt *minirt)
{
	int color;

	color = check_sphere_intersection(ray, minirt);
	if (color != 0)
		return (color);
	color = check_cylinder_intersection(ray, minirt);
	if (color != 0)
		return (color);
	color = check_plane_intersection(ray, minirt);
	if (color != 0)
		return (color);
	return (0);
}

int get_color(int x, int y, t_minirt *minirt)
{
	t_ray *ray;
	int color;

	color = 0;
	ray = send_ray_from_cam(x, y, minirt);
	color = check_intersections(ray, minirt);
	color = calculate_ambient_light(color, minirt->scene->amb_light);
	free_ray(ray);
	return (color);
}
