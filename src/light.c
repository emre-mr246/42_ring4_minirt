#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

static int check_object_shadow(t_ray shadow_ray, void *object, int obj_type, float light_distance)
{
	t_vector *hit;
	float hit_distance;

	if (obj_type == SPHERE)
		hit = intersect_sphere(shadow_ray, *(t_sphere *)object);
	else if (obj_type == CYLINDER)
		hit = intersect_cylinder(shadow_ray, *(t_cylinder *)object);
	else
		return (0);
	if (hit)
	{
		hit_distance = vector_length(subtract_vector(*hit, *shadow_ray.origin));
		if (hit_distance > EPSILON && hit_distance < light_distance)
		{
			free(hit);
			return (1);
		}
		free(hit);
	}
	return (0);
}

int is_in_shadow(t_vector *point, t_light *light, t_minirt *minirt)
{
	t_ray shadow_ray;
	t_vector direction;
	float light_distance;
	int i;

	direction.x = light->pos->x - point->x;
	direction.y = light->pos->y - point->y;
	direction.z = light->pos->z - point->z;
	light_distance = vector_length(&direction);
	normalize_vector(&direction);
	shadow_ray.origin = point;
	shadow_ray.direction = &direction;
	i = 0;
	while (minirt->scene->objects[i])
	{
		if (check_object_shadow(shadow_ray, minirt->scene->objects[i], minirt->scene->obj_tags[i], light_distance))
			return (1);
		i++;
	}
	return (0);
}

float calculate_light_intensity(t_vector *intersection, t_vector *normal, t_minirt *minirt, t_light *light)
{
	t_vector *light_dir;
	float distance;
	float attenuation;
	float dot;
	float intensity;

	intensity = 0;
	light_dir = subtract_vector(*light->pos, *intersection);
	normalize_vector(light_dir);
	dot = dot_product(*normal, *light_dir);
	if (dot > 0)
	{
		if (is_in_shadow(intersection, light, minirt))
		{
			distance = vector_length(light_dir);
			attenuation = 1 / (distance * distance);
			intensity += light->intensity * dot * attenuation;
		}
	}
	free(light_dir);
	return (fmin(fmax(intensity, minirt->scene->amb_light->intensity), 1.0));
}

float check_light_contribution(t_light *light, t_vector offset_point, t_vector *normal, t_minirt *minirt)
{
	float intensity;
	t_vector *light_dir;
	float distance;
	float attenuation;
	float dot;

	intensity = 0;
	light_dir = subtract_vector(*light->pos, offset_point);
	normalize_vector(light_dir);
	dot = dot_product(*normal, *light_dir);
	if (dot > 0)
	{
		if (!is_in_shadow(&offset_point, light, minirt))
		{
			distance = vector_length(light_dir);
			attenuation = 1.0f / (1.0f + distance * 0.05f);
			intensity = light->intensity * dot * attenuation;
		}
	}
	free(light_dir);
	return (intensity);
}

float calculate_illumination(t_vector offset_point, t_vector *normal, t_minirt *minirt)
{
	float intensity;
	int i;

	intensity = minirt->scene->amb_light->intensity;
	i = 0;
	while (minirt->scene->lights[i])
	{
		intensity += check_light_contribution(minirt->scene->lights[i], offset_point, normal, minirt);
		i++;
	}
	return (fmin(fmax(intensity, minirt->scene->amb_light->intensity), 1.0));
}
