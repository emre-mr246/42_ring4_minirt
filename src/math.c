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

float	dot_product(t_vector v, t_vector u)
{
    return ((v.x * u.x) + (v.y * u.y) + (v.z * u.z));
}

t_vector *cross_product(t_vector v, t_vector u)
{
    t_vector *vector;

    vector = (t_vector *)ft_calloc(sizeof(t_vector), 1);
    if (!vector)
        return (NULL);
    vector->x = (u.y * v.z) - (u.z * v.y);
    vector->y = (u.z * v.x) - (u.x * v.z);
    vector->z = (u.x * v.y) - (u.y * v.x);
    return (vector);
}

float	norm(t_vector v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_vector *sum_vector(t_vector v, t_vector u)
{
    t_vector *vector;

    vector = (t_vector *)ft_calloc(sizeof(t_vector), 1);
    if (!vector)
        return (NULL);
    vector->x = v.x + u.x;
    vector->y = v.y + u.y;
    vector->z = v.z + u.z;
    return (vector);
}

t_vector *subtract_vector(t_vector v, t_vector u)
{
    t_vector *vector;

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
    t_vector *vector;

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

t_vector	*get_point_on_ray(t_ray ray, float t)
{
	t_vector *v;
	t_vector *td;
	
	td = copy_vector(*ray.direction);
	scale_vector(td, t);
	v = sum_vector(*ray.origin, *td);
	free(td);
	return (v);
}

t_vector    *intersect_plane(t_ray ray, t_plane plane)
{
    float t;

    // ışın denklemi : pr = o + tD
    // plane denklemi : (pp - pr) . n = 0
    // (pp - (o + tD)) . n = 0
    // (pp - o - tD) . n = 0
    // pp . n - o . n - tD . n = 0
    // pp . n - o . n = t (D . n)
    // t = (pp . n - o . n) / (D . n ) 
    t = (dot_product(*plane.point, *plane.normal) - dot_product(*ray.origin, *plane.normal)) 
            / dot_product(*ray.direction, *plane.normal);
    return (get_point_on_ray(ray, t));
}

float sq(float a)
{
    return (a * a);
}

float   discriminant(float a, float b, float c)
{
    return (sq(b) - (4 * a * c));
}

float   get_min_x(float x1, float x2, t_ray ray)
{
    t_vector *v1;
    t_vector *v2;

    v1 = get_point_on_ray(ray, x1);
    v2 = get_point_on_ray(ray, x2);
    if (norm(*v1) < norm(*v2))
    {
        free(v1);
        free(v2);
        return (x1);
    }
    free(v1);
    free(v2);
    return (x2);
}

float   solve_eq(float a, float b, float c, t_ray ray)
{
    //x = (-b + sqrt(disc)) / 2a
    float disc;
    float   x1;
    float   x2;

    disc = discriminant(a, b, c);
    x1 = (-b + sqrtf(disc)) / (2 * a);
    x2 = (-b - sqrtf(disc)) / (2 * a);
    return (get_min_x(x1, x2, ray));
}

t_vector    *intersect_sphere(t_ray ray, t_sphere sphere)
{
    float a;
    float b;
    float c;

    a = sq(ray.direction->x) + sq(ray.direction->y) + sq(ray.direction->z);
    b = 2 * (ray.origin->x - sphere.origin->x) * ray.direction->x
        + 2 * (ray.origin->y - sphere.origin->y) * ray.direction->y
        + 2 * (ray.origin->z - sphere.origin->z) * ray.direction->z;
    c = sq(ray.origin->x - sphere.origin->x)
        + sq(ray.origin->y - sphere.origin->y) 
        + sq(ray.origin->z - sphere.origin->z)
		- sq(sphere.radius);
    if (discriminant(a, b, c) < 0)
        return (NULL);
    return (get_point_on_ray(ray, solve_eq(a, b, c, ray)));
}
