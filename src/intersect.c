#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

t_vector *intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector vec;
	float discriminant_value;
	float t1;
	float t2;

	vec.x = sq(ray.direction->x) + sq(ray.direction->y) + sq(ray.direction->z);
	vec.y = 2 * ((ray.origin->x - sphere.origin->x) * ray.direction->x +
				 (ray.origin->y - sphere.origin->y) * ray.direction->y +
				 (ray.origin->z - sphere.origin->z) * ray.direction->z);
	vec.z = sq(ray.origin->x - sphere.origin->x) +
			sq(ray.origin->y - sphere.origin->y) +
			sq(ray.origin->z - sphere.origin->z) -
			sq(sphere.radius);
	discriminant_value = discriminant(vec.x, vec.y, vec.z);
	if (discriminant_value < 0)
		return (NULL);
	t1 = (-vec.y - sqrt(discriminant_value)) / (2 * vec.x);
	t2 = (-vec.y + sqrt(discriminant_value)) / (2 * vec.x);
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

static int calculate_cylinder_intersection(t_ray ray, t_cylinder cylinder, float *t1, float *t2)
{
    t_vector vec;
    float discriminant_value;

    vec.x = sq(ray.direction->x) + sq(ray.direction->z);
    vec.y = 2 * (ray.direction->x * (ray.origin->x - cylinder.origin->x) +
                 ray.direction->z * (ray.origin->z - cylinder.origin->z));
    vec.z = sq(ray.origin->x - cylinder.origin->x) + sq(ray.origin->z - cylinder.origin->z) - sq(cylinder.radius);
    discriminant_value = discriminant(vec.x, vec.y, vec.z);
    if (discriminant_value < 0)
        return (0);
    *t1 = (-vec.y - sqrt(discriminant_value)) / (2 * vec.x);
    *t2 = (-vec.y + sqrt(discriminant_value)) / (2 * vec.x);
    return (1);
}

t_vector *intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
    t_vector *point;
    float t1;
    float t2;

    if (!calculate_cylinder_intersection(ray, cylinder, &t1, &t2))
        return (NULL);
    if (t1 >= RAY_T_MIN && t1 <= RAY_T_MAX)
    {
        point = get_point_on_ray(ray, t1);
        if (point->y >= cylinder.origin->y && point->y <= cylinder.origin->y + cylinder.height)
            return (point);
        free(point);
    }
    if (t2 >= RAY_T_MIN && t2 <= RAY_T_MAX)
    {
        point = get_point_on_ray(ray, t2);
        if (point->y >= cylinder.origin->y && point->y <= cylinder.origin->y + cylinder.height)
            return (point);
        free(point);
    }
    return (NULL);
}
