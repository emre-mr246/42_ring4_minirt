/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:16 by emgul             #+#    #+#             */
/*   Updated: 2025/03/17 04:14:05 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <math.h>

float	get_plane_light_intensity(t_plane *plane, t_ray *ray, t_minirt *minirt,
		t_vector *intersection)
{
	t_vector	normal;
	t_vector	*offset_point;
	t_vector	*normal_offset;
	float		light_intensity;

	normal = *plane->normal;
	if (dot_product(normal, *ray->direction) > 0)
		scale_vector(&normal, -1);
	normalize_vector(&normal);
	normal_offset = multiply_vector(normal, EPSILON);
	offset_point = sum_vector(*intersection, *normal_offset);
	free(normal_offset);
	light_intensity = calculate_illumination(*offset_point, &normal,
			minirt);
	free(offset_point);
	return (light_intensity);
}

int	plane_shade(t_plane *plane, t_ray *ray, t_minirt *minirt,
		t_vector *intersection)
{
	t_color	base_color;
	t_color	final_color;
	float	light_intensity;

	light_intensity = get_plane_light_intensity(plane, ray, minirt,
			intersection);
	base_color.r = (plane->color >> 16) & 0xFF;
	base_color.g = (plane->color >> 8) & 0xFF;
	base_color.b = plane->color & 0xFF;
	final_color = apply_intensity(base_color, light_intensity);
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
