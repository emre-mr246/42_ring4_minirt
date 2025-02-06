#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

t_vector *intersect_sphere(t_ray ray, t_sphere sphere)
{
	float a;
	float b;
	float c;

	a = sq(ray.direction->x) + sq(ray.direction->y) + sq(ray.direction->z);
	b = 2 * (ray.origin->x - sphere.origin->x) * ray.direction->x + 2 * (ray.origin->y - sphere.origin->y) * ray.direction->y + 2 * (ray.origin->z - sphere.origin->z) * ray.direction->z;
	c = sq(ray.origin->x - sphere.origin->x) + sq(ray.origin->y - sphere.origin->y) + sq(ray.origin->z - sphere.origin->z) - sq(sphere.radius);
	if (discriminant(a, b, c) < 0)
		return (NULL);
	return (get_point_on_ray(ray, solve_eq(a, b, c, ray)));
}

t_vector *intersect_plane(t_ray ray, t_plane plane)
{
	float dDotN;
	float t;

	dDotN = dot_product(*ray.direction, *plane.normal);
	if (dDotN == 0)
		return (NULL);
	t = (dot_product(*plane.point, *plane.normal) - dot_product(*ray.origin, *plane.normal)) / dDotN;
	if (t < RAY_T_MIN || t > RAY_T_MAX)
		return (NULL);
	return (get_point_on_ray(ray, t));
}