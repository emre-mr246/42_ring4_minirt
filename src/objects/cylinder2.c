/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:27:23 by mitasci           #+#    #+#             */
/*   Updated: 2025/03/17 18:41:11 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

float	calculate_y(t_vector dir, float t, t_vector co, t_vector axis)
{
	t_vector	*temp;
	t_vector	*temp2;
	float		y;

	temp = multiply_vector(dir, t);
	temp2 = sum_vector(co, *temp);
	y = dot_product(*temp2, axis);
	free(temp);
	free(temp2);
	return (y);
}

int	calculate_ts(t_ray ray, t_cylinder cylinder, float *t1, float *t2)
{
	t_vector	*co;
	t_vector	*temp;
	t_vector	*d_perp;
	t_vector	*co_perp;
	t_vector	vec;

	co = subtract_vector(*ray.origin, *cylinder.origin);
	temp = multiply_vector(*cylinder.axis, dot_product(*ray.direction,
				*cylinder.axis));
	d_perp = subtract_vector(*ray.direction, *temp);
	free(temp);
	temp = multiply_vector(*cylinder.axis, dot_product(*co, *cylinder.axis));
	co_perp = subtract_vector(*co, *temp);
	free(co);
	free(temp);
	vec.x = dot_product(*d_perp, *d_perp);
	vec.y = 2 * dot_product(*d_perp, *co_perp);
	vec.z = dot_product(*co_perp, *co_perp) - sq(cylinder.radius);
	free(d_perp);
	free(co_perp);
	if (discriminant(vec.x, vec.y, vec.z) < 0)
		return (1);
	*t1 = (-vec.y - sqrt(discriminant(vec.x, vec.y, vec.z))) / (2 * vec.x);
	*t2 = (-vec.y + sqrt(discriminant(vec.x, vec.y, vec.z))) / (2 * vec.x);
	return (0);
}

static int	calculate_cylinder_intersection(t_ray ray, t_cylinder cylinder,
		float *t1, float *t2)
{
	float		y1;
	float		y2;
	t_vector	*co;

	co = subtract_vector(*ray.origin, *cylinder.origin);
	if (calculate_ts(ray, cylinder, t1, t2))
	{
		free(co);
		return (0);
	}
	y1 = calculate_y(*ray.direction, *t1, *co, *cylinder.axis);
	y2 = calculate_y(*ray.direction, *t2, *co, *cylinder.axis);
	free(co);
	if (y1 < 0 || y1 > cylinder.height)
		*t1 = -1;
	if (y2 < 0 || y2 > cylinder.height)
		*t2 = -1;
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
