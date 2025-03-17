/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:17 by emgul             #+#    #+#             */
/*   Updated: 2025/03/17 20:14:52 by mitasci          ###   ########.fr       */
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
	t_color		light_color;
	t_color		final_color;
	t_vector	offset_point;

	normal = calculate_cylinder_normal(cy, intersection, &offset_point);
	light_color = calculate_illumination(offset_point, normal, minirt);
	final_color.r = clamp_color_value(((cy->color >> 16) & 0xFF)
			* (light_color.r / 255.0f));
	final_color.g = clamp_color_value(((cy->color >> 8) & 0xFF) * (light_color.g
				/ 255.0f));
	final_color.b = clamp_color_value((cy->color & 0xFF) * (light_color.b
				/ 255.0f));
	free(normal);
	return (create_rgb(final_color.r, final_color.g, final_color.b));
}
