/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:15 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 08:46:16 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"

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

int	calculate_sphere_shade(t_sphere *sp, t_minirt *minirt,
		t_vector *intersection)
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
