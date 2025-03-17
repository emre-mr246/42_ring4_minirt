/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:17 by emgul             #+#    #+#             */
/*   Updated: 2025/03/16 23:57:13 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

static t_vector	*calculate_cylinder_normal(t_cylinder *cy,
		t_vector *intersection, t_vector *offset_point)
{
	t_vector	*normal;
	t_vector	*temp_normal;
	t_vector	*proj;

	normal = subtract_vector(*intersection, *cy->origin);
	proj = multiply_vector(*cy->axis, dot_product(*normal, *cy->axis));
	temp_normal = subtract_vector(*normal, *proj);
	free(normal);
	normal = temp_normal;
	normalize_vector(normal);
	free(proj);
	offset_point->x = intersection->x + normal->x * EPSILON;
	offset_point->y = intersection->y + normal->y * EPSILON;
	offset_point->z = intersection->z + normal->z * EPSILON;
	return (normal);
}

int	cylinder_shade(t_cylinder *cy, t_minirt *minirt, t_vector *intersection)
{
	t_vector	*normal;
	t_color		color;
	t_vector	offset_point;
	float		intensity;

	normal = calculate_cylinder_normal(cy, intersection, &offset_point);
	intensity = calculate_illumination(offset_point, normal, minirt);
	color.r = clamp_color_value(((cy->color >> 16) & 0xFF) * intensity);
	color.g = clamp_color_value(((cy->color >> 8) & 0xFF) * intensity);
	color.b = clamp_color_value((cy->color & 0xFF) * intensity);
	free(normal);
	return (create_rgb(color.r, color.g, color.b));
}

static int	calculate_cylinder_intersection(t_ray ray, t_cylinder cylinder,
		float *t1, float *t2)
{
	t_vector	vec;
	float		discriminant_value;

	vec.x = sq(ray.direction->x) + sq(ray.direction->z);
	vec.y = 2 * (ray.direction->x * (ray.origin->x - cylinder.origin->x)
			+ ray.direction->z * (ray.origin->z - cylinder.origin->z));
	vec.z = sq(ray.origin->x - cylinder.origin->x) + sq(ray.origin->z
			- cylinder.origin->z) - sq(cylinder.radius);
	discriminant_value = discriminant(vec.x, vec.y, vec.z);
	if (discriminant_value < 0)
		return (0);
	*t1 = (-vec.y - sqrt(discriminant_value)) / (2 * vec.x);
	*t2 = (-vec.y + sqrt(discriminant_value)) / (2 * vec.x);
	return (1);
}

t_vector	*intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vector	*point;
	float		t1;
	float		t2;

	if (!calculate_cylinder_intersection(ray, cylinder, &t1, &t2))
		return (NULL);
	if (t1 >= RAY_T_MIN && t1 <= RAY_T_MAX)
	{
		point = get_point_on_ray(ray, t1);
		if (point->y >= cylinder.origin->y && point->y <= cylinder.origin->y
			+ cylinder.height)
			return (point);
		free(point);
	}
	if (t2 >= RAY_T_MIN && t2 <= RAY_T_MAX)
	{
		point = get_point_on_ray(ray, t2);
		if (point->y >= cylinder.origin->y && point->y <= cylinder.origin->y
			+ cylinder.height)
			return (point);
		free(point);
	}
	return (NULL);
}
