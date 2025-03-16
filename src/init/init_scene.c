/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:25:11 by emgul             #+#    #+#             */
/*   Updated: 2025/03/16 15:37:36 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

t_amb_light	*init_amb_light(char **arr)
{
	t_amb_light	*amb_light;

	amb_light = (t_amb_light *)ft_calloc(sizeof(t_amb_light), 1);
	if (!amb_light)
		return (NULL);
	amb_light->intensity = fmin(fmax(ft_atof(arr[1]), 0.0), 1.0);
	amb_light->color = parse_color(arr[2]);
	return (amb_light);
}

t_camera	*init_camera(char **arr)
{
	t_camera	*camera;
	double		length;

	camera = (t_camera *)ft_calloc(sizeof(t_camera), 1);
	if (!camera)
		return (NULL);
	camera->pos = init_vector_str(arr[1]);
	camera->orientation = init_vector_str(arr[2]);
	if (camera->orientation->x == 0 && camera->orientation->y == 0
		&& camera->orientation->z == 0)
		camera->orientation->x = EPSILON;
	camera->orientation->x = fmin(fmax(camera->orientation->x, -1.0), 1.0);
	camera->orientation->y = fmin(fmax(camera->orientation->y, -1.0), 1.0);
	camera->orientation->z = fmin(fmax(camera->orientation->z, -1.0), 1.0);
	length = sqrt(camera->orientation->x * camera->orientation->x
			+ camera->orientation->y * camera->orientation->y
			+ camera->orientation->z * camera->orientation->z);
	camera->orientation->x /= length;
	camera->orientation->y /= length;
	camera->orientation->z /= length;
	camera->fov = clamp(ft_atoi(arr[3]), 0, 180);
	return (camera);
}

void	fill_objects(t_scene *scene, char **split)
{
	int	i;

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
}

void	update_viewport_with_fov(t_scene *scene)
{
	double	fov_rad;
	double	aspect_ratio;

	if (!scene->camera || !scene->viewport)
		return ;
	fov_rad = scene->camera->fov * M_PI / 180.0;
	aspect_ratio = (double)WIN_W / WIN_H;
	scene->viewport->height = 2.0 * tan(fov_rad / 2.0);
	scene->viewport->width = scene->viewport->height * aspect_ratio;
}

int	parse_line(char *line, void *scene_data)
{
	t_scene	*scene;
	char	**split;

	scene = (t_scene *)scene_data;
	split = ft_split_charset(line, " \t");
	if (strs_equal(split[0], "A"))
		scene->amb_light = init_amb_light(split);
	if (strs_equal(split[0], "C"))
	{
		scene->camera = init_camera(split);
		update_viewport_with_fov(scene);
	}
	if (strs_equal(split[0], "L"))
		init_light(scene, split);
	fill_objects(scene, split);
	free_array(split);
	return (0);
}
