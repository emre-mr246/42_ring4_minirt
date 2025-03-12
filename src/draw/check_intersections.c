#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

static t_vector *get_intersection(t_ray *ray, void *object, int obj_type)
{
	t_vector *intersection;

	intersection = NULL;
	if (obj_type == SPHERE)
		intersection = intersect_sphere(*ray, *(t_sphere *)object);
	else if (obj_type == CYLINDER)
		intersection = intersect_cylinder(*ray, *(t_cylinder *)object);
	else if (obj_type == PLANE)
		intersection = intersect_plane(*ray, *(t_plane *)object);
	return (intersection);
}

static int check_object_intersection(t_ray *ray, void *object, int obj_type, t_minirt *minirt)
{
	t_vector *intersection;
	int color;

	color = 0;
	intersection = get_intersection(ray, object, obj_type);
	if (intersection)
	{
		float distance = calculate_distance(ray->origin, intersection);
		if (obj_type == SPHERE)
			((t_sphere *)object)->distance = distance;
		else if (obj_type == CYLINDER)
			((t_cylinder *)object)->distance = distance;
		else if (obj_type == PLANE)
			((t_plane *)object)->distance = distance;
		if (obj_type == SPHERE)
			color = calculate_sphere_shade((t_sphere *)object, minirt, intersection);
		else if (obj_type == CYLINDER)
			color = calculate_cylinder_shade((t_cylinder *)object, minirt, intersection);
		else if (obj_type == PLANE)
			color = calculate_plane_shade((t_plane *)object, ray, minirt, intersection);
		free(intersection);
	}
	return (color);
}

static int find_closest_intersection(t_minirt *minirt, int *colors, float *distances)
{
	int i;
	int closest_index;
	float min_distance;

	closest_index = -1;
	min_distance = INFINITY;
	i = 0;
	while (minirt->scene->objects[i])
	{
		if (colors[i] != 0)
		{
			if (distances[i] < min_distance)
			{
				min_distance = distances[i];
				closest_index = i;
			}
		}
		i++;
	}
	if (closest_index == -1)
		return (0);
	return (colors[closest_index]);
}

int *check_object_colors(t_ray *ray, t_minirt *minirt, float *distances)
{
	int i;
	int color;
	int *colors;

	colors = ft_calloc(minirt->scene->object_count + 1, sizeof(int));
	if (!colors)
		return (NULL);
	i = 0;
	while (minirt->scene->objects[i])
	{
		color = check_object_intersection(ray, minirt->scene->objects[i],
										  minirt->scene->obj_tags[i], minirt);
		colors[i] = color;
		if (color != 0)
		{
			if (minirt->scene->obj_tags[i] == SPHERE)
				distances[i] = ((t_sphere *)minirt->scene->objects[i])->distance;
			else if (minirt->scene->obj_tags[i] == CYLINDER)
				distances[i] = ((t_cylinder *)minirt->scene->objects[i])->distance;
			else if (minirt->scene->obj_tags[i] == PLANE)
				distances[i] = ((t_plane *)minirt->scene->objects[i])->distance;
		}
		else
			distances[i] = INFINITY;
		i++;
	}
	return (colors);
}

int check_intersections(t_ray *ray, t_minirt *minirt)
{
	int *colors;
	float *distances;
	int result;

	distances = ft_calloc(minirt->scene->object_count + 1, sizeof(float));
	if (!distances)
		return (0);
	colors = check_object_colors(ray, minirt, distances);
	if (!colors)
	{
		free(distances);
		return (0);
	}
	result = find_closest_intersection(minirt, colors, distances);
	free(colors);
	free(distances);
	return (result);
}
