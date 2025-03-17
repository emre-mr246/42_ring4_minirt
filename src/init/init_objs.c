/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:24:29 by emgul             #+#    #+#             */
/*   Updated: 2025/03/17 19:13:00 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

void	init_light(t_scene *scene, char **arr)
{
	t_light	*light;
	int		i;

	i = 0;
	while (scene->lights[i])
		i++;
	if (i >= 10)
		ft_exit("too many lights", -1, NULL);
	light = (t_light *)ft_calloc(sizeof(t_light), 1);
	if (!light)
		ft_exit("light malloc", -1, NULL);
	light->pos = init_vector_str(arr[1], 1000.0, -1000.0);
	light->intensity = fmax(fmin(ft_atof(arr[2]), 0.0), 1.0);
	light->color = parse_color(arr[3]);
	scene->lights[i] = light;
}

t_plane	*init_plane(char **arr)
{
	t_plane	*plane;

	plane = (t_plane *)ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		return (NULL);
	plane->point = init_vector_str(arr[1], 1000.0, -1000.0);
	plane->normal = init_vector_str(arr[2], 1.0, -1.0);
	normalize_vector(plane->normal);
	plane->color = parse_color(arr[3]);
	return (plane);
}

t_sphere	*init_sphere(char **arr)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_calloc(sizeof(t_sphere), 1);
	if (!sphere)
		return (NULL);
	sphere->origin = init_vector_str(arr[1], 1000.0, -1000.0);
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
	cylinder->origin = init_vector_str(arr[1], 1000.0, -1000.0);
	cylinder->axis = init_vector_str(arr[2], 1.0, -1.0);
	normalize_vector(cylinder->axis);
	cylinder->radius = atof(arr[3]);
	cylinder->height = atof(arr[4]);
	cylinder->color = parse_color(arr[5]);
	return (cylinder);
}
