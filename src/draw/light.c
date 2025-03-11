#include "minirt.h"
#include "libft.h"
#include <math.h>

t_ray create_shadow_ray(t_vector *point, t_light *light)
{
	t_ray shadow_ray;
	t_vector *direction;
	t_vector *tmp;

	tmp = subtract_vector(*light->pos, *point);
	direction = copy_vector(*tmp);
	free(tmp);
	normalize_vector(direction);
	shadow_ray.origin = copy_vector(*point);
	shadow_ray.direction = direction;
	return (shadow_ray);
}

int check_shadow_intersections(t_ray shadow_ray, float light_dist, t_minirt *minirt)
{
	t_vector *intersection;
	int i;
	float obj_dist;

	i = 0;
	while (minirt->scene->objects[i])
	{
		intersection = NULL;
		if (minirt->scene->obj_tags[i] == SPHERE)
			intersection = intersect_sphere(shadow_ray, *(t_sphere *)minirt->scene->objects[i]);
		else if (minirt->scene->obj_tags[i] == CYLINDER)
			intersection = intersect_cylinder(shadow_ray, *(t_cylinder *)minirt->scene->objects[i]);
		else if (minirt->scene->obj_tags[i] == PLANE)
			intersection = intersect_plane(shadow_ray, *(t_plane *)minirt->scene->objects[i]);
		if (intersection)
		{
			obj_dist = calculate_distance(shadow_ray.origin, intersection);
			free(intersection);
			if (obj_dist < light_dist - EPSILON)
				return (1);
		}
		i++;
	}
	return (0);
}

int is_in_shadow(t_vector *point, t_light *light, t_minirt *minirt)
{
	t_ray shadow_ray;
	float light_dist;
	int result;

	shadow_ray = create_shadow_ray(point, light);
	light_dist = calculate_distance(point, light->pos);
	result = check_shadow_intersections(shadow_ray, light_dist, minirt);
	free(shadow_ray.origin);
	free(shadow_ray.direction);
	return (result);
}

float check_light_contribution(t_light *light, t_vector point, t_vector *normal, t_minirt *minirt)
{
	t_vector *light_dir;
	t_vector *tmp;
	float contribution;
	float intensity;

	if (is_in_shadow(&point, light, minirt))
		return (0);
	tmp = subtract_vector(*light->pos, point);
	light_dir = copy_vector(*tmp);
	free(tmp);
	normalize_vector(light_dir);
	contribution = dot_product(*normal, *light_dir);
	free(light_dir);
	if (contribution < 0)
		contribution = 0;
	intensity = contribution * light->intensity;
	return (intensity);
}

float calculate_illumination(t_vector point, t_vector *normal, t_minirt *minirt)
{
	int i;
	float total_light;
	float ambient;

	ambient = minirt->scene->amb_light->intensity;
	total_light = ambient;
	i = 0;
	while (minirt->scene->lights[i])
	{
		total_light += check_light_contribution(minirt->scene->lights[i], point, normal, minirt);
		i++;
	}
	if (total_light > 1.0f)
		total_light = 1.0f;
	return (total_light);
}
