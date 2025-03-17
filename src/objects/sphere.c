/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:15 by emgul             #+#    #+#             */
/*   Updated: 2025/03/17 20:11:03 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <math.h>

static t_vector	*calculate_sphere_normal(t_sphere *sp, t_vector *intersection,
		t_vector *offset_point)
{
	t_vector	*normal;

	normal = subtract_vector(*intersection, *sp->origin);
	normalize_vector(normal);
	offset_point->x = intersection->x + normal->x * EPSILON;
	offset_point->y = intersection->y + normal->y * EPSILON;
	offset_point->z = intersection->z + normal->z * EPSILON;
	return (normal);
}

int	sphere_shade(t_sphere *sp, t_minirt *minirt, t_vector *intersection)
{
	t_vector	*normal;
	t_color		light_color;
	t_color		final_color;
	t_vector	offset_point;

	normal = calculate_sphere_normal(sp, intersection, &offset_point);
	light_color = calculate_illumination(offset_point, normal, minirt);
	final_color.r = clamp_color_value(((sp->color >> 16) & 0xFF) * (light_color.r / 255.0f));
	final_color.g = clamp_color_value(((sp->color >> 8) & 0xFF) * (light_color.g / 255.0f));
	final_color.b = clamp_color_value((sp->color & 0xFF) * (light_color.b / 255.0f));
	free(normal);
	return (create_rgb(final_color.r, final_color.g, final_color.b));
}

t_vector	*intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	vec;
	float		discriminant_value;
	float		t1;
	float		t2;

	vec.x = sq(ray.direction->x) + sq(ray.direction->y) + sq(ray.direction->z);
	vec.y = 2 * ((ray.origin->x - sphere.origin->x) * ray.direction->x
			+ (ray.origin->y - sphere.origin->y) * ray.direction->y
			+ (ray.origin->z - sphere.origin->z) * ray.direction->z);
	vec.z = sq(ray.origin->x - sphere.origin->x) + sq(ray.origin->y
			- sphere.origin->y) + sq(ray.origin->z - sphere.origin->z)
		- sq(sphere.radius);
	discriminant_value = discriminant(vec.x, vec.y, vec.z);
	if (discriminant_value < 0)
		return (NULL);
	t1 = (-vec.y - sqrt(discriminant_value)) / (2 * vec.x);
	t2 = (-vec.y + sqrt(discriminant_value)) / (2 * vec.x);
	if (t1 >= RAY_T_MIN && t1 <= RAY_T_MAX)
		return (get_point_on_ray(ray, t1));
	if (t2 >= RAY_T_MIN && t2 <= RAY_T_MAX)
		return (get_point_on_ray(ray, t2));
	return (NULL);
}
