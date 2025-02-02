/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:33:30 by emgul             #+#    #+#             */
/*   Updated: 2024/10/17 19:03:39 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"

t_vector *init_vector_str(char *str)
{
	char **split;
    t_vector *v;

    v = (t_vector *)ft_calloc(sizeof(t_vector), 1);
    if (!v)
        return (NULL);
	split = ft_split(str, ',');
	v->x = ft_atof(split[0]);
    v->y = ft_atof(split[1]);
    v->z = ft_atof(split[2]);
	free_array(split);
	return (v);
}

t_vector *init_vector(float x, float y, float z)
{
    t_vector *v;

    v = (t_vector *)ft_calloc(sizeof(t_vector), 1);
    if (!v)
        return (NULL);
	v->x = x;
    v->y = y;
    v->z = z;
	return (v);
}

t_ray *init_ray(t_vector o, t_vector dir)
{
    t_ray *ray;

    ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
    if (!ray)
        return (NULL);
    ray->origin = init_vector(o.x, o.y, o.z);
    ray->direction = init_vector(dir.x, dir.y, dir.z);
    return (ray);
}

t_scene *init_scene()
{
    t_scene *scene;

    scene = (t_scene *)ft_calloc(sizeof(t_scene), 1);
    if (!scene)
        return (NULL);
	return (scene);
}

void fill_scene(t_minirt *minirt, t_input *input)
{
    t_scene *scene;
    
    scene = minirt->scene;
    scene->amb_light = (t_amb_light *)ft_calloc(sizeof(t_amb_light), 1);
    scene->camera = (t_camera *)ft_calloc(sizeof(t_camera), 1);
    scene->viewport = (t_viewport *)ft_calloc(sizeof(t_viewport), 1);
    scene->viewport->width = WIN_W / 100;
    scene->viewport->height = WIN_H / 100;
    scene->objects = (void **)ft_calloc(sizeof(void *), input->obj_count + 1);
    scene->obj_tags = (int *)ft_calloc(sizeof(int), input->obj_count + 1);
    if (!scene->amb_light || !scene->camera || !scene->viewport
             || !scene->objects || !scene->obj_tags)
        ft_exit("scene_malloc", -1, minirt);
}

t_minirt *init_minirt()
{
    t_minirt *minirt;
    
    minirt = (t_minirt *)ft_calloc(sizeof(t_minirt), 1);
    if (!minirt)
        ft_exit("init_minirt", -1, minirt);
	minirt->mlx = mlx_init();
	minirt->win_height = WIN_H;
	minirt->win_width = WIN_W;
	minirt->win = mlx_new_window(minirt->mlx, minirt->win_width,
			minirt->win_height, "RaRe Tracer");
	minirt->img.ptr = mlx_new_image(minirt->mlx, minirt->win_width, minirt->win_height);
	minirt->img.data = mlx_get_data_addr(minirt->img.ptr, &minirt->img.bits_per_pixel,
			&minirt->img.line_len, &minirt->img.endian);
    minirt->scene = init_scene();
    if (!minirt->scene)
        ft_exit("init_scene", -1, minirt);
    return (minirt);
}
