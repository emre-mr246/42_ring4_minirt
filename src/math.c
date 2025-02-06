/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:27:39 by emgul             #+#    #+#             */
/*   Updated: 2024/10/17 19:24:36 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

float dot_product(t_vector v, t_vector u)
{
	return ((v.x * u.x) + (v.y * u.y) + (v.z * u.z));
}

t_vector *cross_product(const t_vector *v, const t_vector *u)
{
	if (!v || !u)
		return NULL;

	t_vector *vector = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!vector)
		return NULL;

	vector->x = (u->y * v->z) - (u->z * v->y);
	vector->y = (u->z * v->x) - (u->x * v->z);
	vector->z = (u->x * v->y) - (u->y * v->x);

	return vector;
}

t_vector *get_point_on_ray(t_ray ray, float t)
{
	t_vector *v;
	t_vector *td;

	td = copy_vector(*ray.direction);
	scale_vector(td, t);
	v = sum_vector(*ray.origin, *td);
	free(td);
	return (v);
}

float sq(float a)
{
	return (a * a);
}

float discriminant(float a, float b, float c)
{
	return (sq(b) - (4 * a * c));
}

float get_min_x(float x1, float x2, t_ray ray)
{
	t_vector *v1;
	t_vector *v2;

	v1 = get_point_on_ray(ray, x1);
	v2 = get_point_on_ray(ray, x2);
	if (vector_magnitude(*v1) < vector_magnitude(*v2))
	{
		free(v1);
		free(v2);
		return (x1);
	}
	free(v1);
	free(v2);
	return (x2);
}

float solve_eq(float a, float b, float c, t_ray ray)
{
	// x = (-b + sqrt(disc)) / 2a
	float disc;
	float x1;
	float x2;

	disc = discriminant(a, b, c);
	x1 = (-b + sqrtf(disc)) / (2 * a);
	x2 = (-b - sqrtf(disc)) / (2 * a);
	return (get_min_x(x1, x2, ray));
}
