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
	float discriminant_value;
	float t1;
	float t2;

	a = sq(ray.direction->x) + sq(ray.direction->y) + sq(ray.direction->z);
	b = 2 * ((ray.origin->x - sphere.origin->x) * ray.direction->x +
			 (ray.origin->y - sphere.origin->y) * ray.direction->y +
			 (ray.origin->z - sphere.origin->z) * ray.direction->z);
	c = sq(ray.origin->x - sphere.origin->x) +
		sq(ray.origin->y - sphere.origin->y) +
		sq(ray.origin->z - sphere.origin->z) -
		sq(sphere.radius);
	discriminant_value = discriminant(a, b, c);
	if (discriminant_value < 0)
		return (NULL);
	t1 = (-b - sqrt(discriminant_value)) / (2 * a);
	t2 = (-b + sqrt(discriminant_value)) / (2 * a);
	if (t1 >= RAY_T_MIN && t1 <= RAY_T_MAX)
		return (get_point_on_ray(ray, t1));
	if (t2 >= RAY_T_MIN && t2 <= RAY_T_MAX)
		return (get_point_on_ray(ray, t2));
	return (NULL);
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
