/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:15 by emgul             #+#    #+#             */
/*   Updated: 2025/03/16 23:58:03 by emgul            ###   ########.fr       */
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
	t_color		color;
	t_vector	offset_point;
	float		intensity;

	normal = calculate_sphere_normal(sp, intersection, &offset_point);
	intensity = calculate_illumination(offset_point, normal, minirt);
	color.r = clamp_color_value(((sp->color >> 16) & 0xFF) * intensity);
	color.g = clamp_color_value(((sp->color >> 8) & 0xFF) * intensity);
	color.b = clamp_color_value((sp->color & 0xFF) * intensity);
	free(normal);
	return (create_rgb(color.r, color.g, color.b));
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
