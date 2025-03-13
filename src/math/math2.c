/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:08:16 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 08:46:24 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

float	vector_length_2d(float a, float b)
{
	return (sqrt(a * a + b * b));
}

float	vector_length(t_vector *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

float	calculate_distance(t_vector *a, t_vector *b)
{
	return (sqrt(sq(a->x - b->x) + sq(a->y - b->y) + sq(a->z - b->z)));
}

float	dist_from_viewport_origin(int x, int y, t_minirt *minirt)
{
	t_viewport	*viewport;
	int			origin_x;
	int			origin_y;

	viewport = minirt->scene->viewport;
	origin_x = viewport->width / 2;
	origin_y = viewport->height / 2;
	return (vector_length_2d(fabsf((float)x - (float)origin_x), fabsf((float)y
				- (float)origin_y)));
}

t_vector	*scale_and_normalize(t_vector *v, float scalar)
{
	t_vector	*scaled_vector;

	scaled_vector = copy_vector(*v);
	scale_vector(scaled_vector, scalar);
	return (scaled_vector);
}
