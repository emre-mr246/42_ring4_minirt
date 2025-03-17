/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:16 by emgul             #+#    #+#             */
/*   Updated: 2025/03/17 20:13:56 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <math.h>

t_color	get_plane_light_color(t_plane *plane, t_ray *ray, t_minirt *minirt,
		t_vector *intersection)
{
	t_vector	normal;
	t_vector	*offset_point;
	t_vector	*normal_offset;
	t_color		light_color;

	normal = *plane->normal;
	if (dot_product(normal, *ray->direction) > 0)
		scale_vector(&normal, -1);
	normalize_vector(&normal);
	normal_offset = multiply_vector(normal, EPSILON);
	offset_point = sum_vector(*intersection, *normal_offset);
	free(normal_offset);
	light_color = calculate_illumination(*offset_point, &normal, minirt);
	free(offset_point);
	return (light_color);
}

int	plane_shade(t_plane *plane, t_ray *ray, t_minirt *minirt,
		t_vector *intersection)
{
	t_color	base_color;
	t_color	final_color;
	t_color	light_color;

	light_color = get_plane_light_color(plane, ray, minirt,
			intersection);
	base_color.r = (plane->color >> 16) & 0xFF;
	base_color.g = (plane->color >> 8) & 0xFF;
	base_color.b = plane->color & 0xFF;
	final_color.r = clamp_color_value(base_color.r * (light_color.r / 255.0f));
	final_color.g = clamp_color_value(base_color.g * (light_color.g / 255.0f));
	final_color.b = clamp_color_value(base_color.b * (light_color.b / 255.0f));
	return (create_rgb(final_color.r, final_color.g, final_color.b));
}

t_vector	*intersect_plane(t_ray ray, t_plane plane)
{
	float	d_dot_n;
	float	t;

	d_dot_n = dot_product(*ray.direction, *plane.normal);
	if (d_dot_n == 0)
		return (NULL);
	t = (dot_product(*plane.point, *plane.normal) - dot_product(*ray.origin,
				*plane.normal)) / d_dot_n;
	if (t < RAY_T_MIN || t > RAY_T_MAX)
		return (NULL);
	return (get_point_on_ray(ray, t));
}
