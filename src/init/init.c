/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:33:30 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 10:47:20 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"

t_vector	*init_vector(float x, float y, float z)
{
	t_vector	*v;

	v = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!v)
		return (NULL);
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

t_ray	*init_ray(t_vector o, t_vector dir)
{
	t_ray	*ray;

	ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (!ray)
		return (NULL);
	ray->origin = init_vector(o.x, o.y, o.z);
	ray->direction = init_vector(dir.x, dir.y, dir.z);
	return (ray);
}

static t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)ft_calloc(sizeof(t_scene), 1);
	if (!scene)
		ft_exit("scene_malloc", -1, NULL);
	scene->lights = (t_light **)ft_calloc(sizeof(t_light *), 10);
	if (!scene->lights)
		ft_exit("scene_lights_malloc", -1, NULL);
	return (scene);
}

void	fill_scene(t_minirt *minirt, t_input *input)
{
	t_scene	*scene;

	scene = minirt->scene;
	scene->amb_light = NULL;
	scene->camera = NULL;
	scene->viewport = (t_viewport *)ft_calloc(sizeof(t_viewport), 1);
	scene->objects = (void **)ft_calloc(sizeof(void *), input->obj_count + 144);
	scene->obj_tags = (int *)ft_calloc(sizeof(int), input->obj_count + 144);
	scene->object_count = input->obj_count;
	if (!scene->viewport || !scene->objects || !scene->obj_tags)
		ft_exit("scene_malloc", -1, minirt);
}

t_minirt	*init_minirt(void)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)ft_calloc(sizeof(t_minirt), 1);
	if (!minirt)
		ft_exit("init_minirt", -1, minirt);
	minirt->mlx = mlx_init();
	minirt->win_height = WIN_H;
	minirt->win_width = WIN_W;
	minirt->win = mlx_new_window(minirt->mlx, minirt->win_width,
			minirt->win_height, "RaRe Tracer");
	minirt->img.ptr = mlx_new_image(minirt->mlx, minirt->win_width,
			minirt->win_height);
	minirt->img.data = mlx_get_data_addr(minirt->img.ptr,
			&minirt->img.bits_per_pixel, &minirt->img.line_len,
			&minirt->img.endian);
	minirt->scene = init_scene();
	if (!minirt->scene)
		ft_exit("init_scene", -1, minirt);
	return (minirt);
}
