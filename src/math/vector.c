/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:20 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 08:46:21 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

t_vector	*sum_vector(t_vector v, t_vector u)
{
	t_vector	*vector;

	vector = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!vector)
		return (NULL);
	vector->x = v.x + u.x;
	vector->y = v.y + u.y;
	vector->z = v.z + u.z;
	return (vector);
}

t_vector	*multiply_vector(t_vector vector, float scalar)
{
	t_vector	*result;

	result = (t_vector *)malloc(sizeof(t_vector));
	if (!result)
		return (NULL);
	result->x = vector.x * scalar;
	result->y = vector.y * scalar;
	result->z = vector.z * scalar;
	return (result);
}

t_vector	*subtract_vector(t_vector v, t_vector u)
{
	t_vector	*vector;

	vector = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!vector)
		return (NULL);
	vector->x = v.x - u.x;
	vector->y = v.y - u.y;
	vector->z = v.z - u.z;
	return (vector);
}

t_vector	*copy_vector(t_vector v)
{
	t_vector	*vector;

	vector = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!vector)
		return (NULL);
	vector->x = v.x;
	vector->y = v.y;
	vector->z = v.z;
	return (vector);
}

void	scale_vector(t_vector *v, float s)
{
	v->x *= s;
	v->y *= s;
	v->z *= s;
}
