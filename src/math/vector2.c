/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:19 by emgul             #+#    #+#             */
/*   Updated: 2025/03/16 15:36:23 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

float	vector_magnitude(t_vector v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

float	vector_magnitude_sq(t_vector v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

void	normalize_vector(t_vector *v)
{
	float	magnitude;

	magnitude = vector_magnitude(*v);
	if (magnitude > 0.0f)
	{
		v->x /= magnitude;
		v->y /= magnitude;
		v->z /= magnitude;
	}
}

t_vector	*normalized_vector(t_vector v)
{
	t_vector	*vector;

	vector = copy_vector(v);
	normalize_vector(vector);
	return (vector);
}
