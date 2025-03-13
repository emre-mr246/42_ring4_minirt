/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:24:29 by emgul             #+#    #+#             */
/*   Updated: 2024/10/03 16:20:30 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

void	init_lights(t_scene *scene)
{
	int	i;
	int	k;
	int	count;

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

t_light	*init_light(char **arr)
{
	t_light	*light;

	light = (t_light *)ft_calloc(sizeof(t_light), 1);
	if (!light)
		return (NULL);
	light->pos = init_vector_str(arr[1]);
	light->intensity = fmax(fmin(ft_atof(arr[2]), 0.0), 1.0);
	light->color = parse_color(arr[3]);
	return (light);
}

t_plane	*init_plane(char **arr)
{
	t_plane	*plane;

	plane = (t_plane *)ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		return (NULL);
	plane->point = init_vector_str(arr[1]);
	plane->normal = init_vector_str(arr[2]);
	plane->color = parse_color(arr[3]);
	return (plane);
}

t_sphere	*init_sphere(char **arr)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_calloc(sizeof(t_sphere), 1);
	if (!sphere)
		return (NULL);
	sphere->origin = init_vector_str(arr[1]);
	sphere->radius = ft_atof(arr[2]);
	sphere->color = parse_color(arr[3]);
	return (sphere);
}

t_cylinder	*init_cylinder(char **arr)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)ft_calloc(sizeof(t_cylinder), 1);
	if (!cylinder)
		return (NULL);
	cylinder->origin = init_vector_str(arr[1]);
	cylinder->axis = init_vector_str(arr[2]);
	cylinder->radius = atof(arr[3]);
	cylinder->height = atof(arr[4]);
	cylinder->color = parse_color(arr[5]);
	return (cylinder);
}
