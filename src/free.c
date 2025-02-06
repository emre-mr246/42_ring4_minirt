#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include "stdlib.h"

static void free_objects(t_scene *scene)
{
	if (scene->objects)
	{
		int i = 0;
		while (scene->objects[i])
		{
			if (scene->obj_tags[i] == LIGHT)
				free_light(scene->objects[i]);
			if (scene->obj_tags[i] == PLANE)
				free_plane(scene->objects[i]);
			if (scene->obj_tags[i] == SPHERE)
				free_sphere(scene->objects[i]);
			if (scene->obj_tags[i] == CYLINDER)
				free_cylinder(scene->objects[i]);
			i++;
		}
		free(scene->objects);
	}
	if (scene->obj_tags)
		free(scene->obj_tags);
}

static void free_scene(t_scene *scene)
{
	if (scene)
	{
		if (scene->camera)
		{
			if (scene->camera->pos)
				free(scene->camera->pos);
			if (scene->camera->orientation)
				free(scene->camera->orientation);
			free(scene->camera);
		}
		if (scene->amb_light)
			free(scene->amb_light);
		if (scene->viewport)
			free(scene->viewport);
		free_objects(scene);
		free(scene);
	}
}

static void free_img(t_minirt *minirt)
{
	if (minirt && minirt->mlx && minirt->img.ptr)
	{
		mlx_destroy_image(minirt->mlx, minirt->img.ptr);
		minirt->img.ptr = NULL;
		minirt->img.data = NULL;
	}
}

void free_minirt(t_minirt *minirt)
{
	if (!minirt)
		return;
	if (minirt->scene)
		free_scene(minirt->scene);
	if (minirt->img.data)
		free_img(minirt);
	if (minirt->mlx)
	{
		mlx_destroy_window(minirt->mlx, minirt->win);
		mlx_destroy_display(minirt->mlx);
		free(minirt->mlx);
	}
	free(minirt);
}

void free_ray(t_ray *ray)
{
	if (ray->direction)
		free(ray->direction);
	if (ray->origin)
		free(ray->origin);
	if (ray)
		free(ray);
}

void free_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}