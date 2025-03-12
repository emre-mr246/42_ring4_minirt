/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:25:11 by emgul             #+#    #+#             */
/*   Updated: 2024/10/17 19:31:36 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <math.h>

t_amb_light *init_amb_light(char **arr)
{
	t_amb_light *amb_light;

	amb_light = (t_amb_light *)ft_calloc(sizeof(t_amb_light), 1);
	if (!amb_light)
		return (NULL);
	amb_light->intensity = fmin(fmax(ft_atof(arr[1]), 0.0), 1.0);
	amb_light->color = parse_color(arr[2]);
	return (amb_light);
}

t_camera *init_camera(char **arr)
{
	t_camera *camera;

	camera = (t_camera *)ft_calloc(sizeof(t_camera), 1);
	if (!camera)
		return (NULL);
	camera->pos = init_vector_str(arr[1]);
	camera->orientation = init_vector_str(arr[2]);
	camera->fov = ft_atoi(arr[3]);
	return (camera);
}

void fill_objects(t_scene *scene, char **split)
{
	int i;

	i = 0;
	if (strs_equal(split[0], "sp"))
	{
		while (scene->objects[i])
			i++;
		scene->objects[i] = init_sphere(split);
		scene->obj_tags[i] = SPHERE;
	}
	if (strs_equal(split[0], "pl"))
	{
		while (scene->objects[i])
			i++;
		scene->objects[i] = init_plane(split);
		scene->obj_tags[i] = PLANE;
	}
	if (strs_equal(split[0], "cy"))
	{
		while (scene->objects[i])
			i++;
		scene->objects[i] = init_cylinder(split);
		scene->obj_tags[i] = CYLINDER;
	}
	if (strs_equal(split[0], "L"))
	{
		while (scene->objects[i])
			i++;
		scene->objects[i] = init_light(split);
		scene->obj_tags[i] = LIGHT;
	}
}

void init_lights(t_scene *scene)
{
	int i;
	int k;
	int count;

	i = 0;
	count = 0;
	while (scene->objects[i])
	{
		if (scene->obj_tags[i] == LIGHT)
			count++;
		i++;
	}
	scene->lights = (t_light **)ft_calloc(sizeof(t_light *), count + 1);
	if (!scene->lights)
		return ;
	i = 0;
	k = 0;
	while (scene->objects[i])
	{
		if (scene->obj_tags[i] == LIGHT)
			scene->lights[k++] = (t_light *)scene->objects[i];
		i++;
	}
	scene->lights[k] = NULL;
}

int parse_line(char *line, void *scene_data)
{
	t_scene *scene;
	char **split;

	scene = (t_scene *)scene_data;
	split = ft_split_charset(line, " \t");
	if (strs_equal(split[0], "A"))
		scene->amb_light = init_amb_light(split);
	if (strs_equal(split[0], "C"))
		scene->camera = init_camera(split);
	fill_objects(scene, split);
	// TODO camera için değişen bir şey yok. fov vs. güncellenmeli
	free_array(split);
	return (0);
}
