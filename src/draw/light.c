/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:31 by emgul             #+#    #+#             */
/*   Updated: 2025/03/17 20:08:57 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <math.h>

t_ray	create_shadow_ray(t_vector *point, t_light *light)
{
	t_ray		shadow_ray;
	t_vector	*direction;
	t_vector	*tmp;

	tmp = subtract_vector(*light->pos, *point);
	direction = copy_vector(*tmp);
	free(tmp);
	normalize_vector(direction);
	shadow_ray.origin = copy_vector(*point);
	shadow_ray.direction = direction;
	return (shadow_ray);
}

int	check_shadow_intersections(t_ray r, float light_dist,
		t_minirt *rt)
{
	t_vector	*isec;
	float		obj_dist;
	int			i;

	i = 0;
	while (rt->scene->objects[i])
	{
		isec = NULL;
		if (rt->scene->obj_tags[i] == SPHERE)
			isec = intersect_sphere(r, *(t_sphere *)rt->scene->objects[i]);
		else if (rt->scene->obj_tags[i] == CYLINDER)
			isec = intersect_cylinder(r, *(t_cylinder *)rt->scene->objects[i]);
		else if (rt->scene->obj_tags[i] == PLANE)
			isec = intersect_plane(r, *(t_plane *)rt->scene->objects[i]);
		if (isec)
		{
			obj_dist = calculate_distance(r.origin, isec);
			free(isec);
			if (obj_dist < light_dist - EPSILON)
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_in_shadow(t_vector *point, t_light *light, t_minirt *minirt)
{
	t_ray	shadow_ray;
	float	light_dist;
	int		result;

	shadow_ray = create_shadow_ray(point, light);
	light_dist = calculate_distance(point, light->pos);
	result = check_shadow_intersections(shadow_ray, light_dist, minirt);
	free(shadow_ray.origin);
	free(shadow_ray.direction);
	return (result);
}

t_color	check_light_contribution(t_light *light, t_vector point,
		t_vector *normal, t_minirt *minirt)
{
	t_vector	*light_dir;
	t_vector	*tmp;
	t_color		contribution;
	float		intensity;

	contribution.r = 0;
	contribution.g = 0;
	contribution.b = 0;
 	if (is_in_shadow(&point, light, minirt))
		return (contribution);
	tmp = subtract_vector(*light->pos, point);
	light_dir = copy_vector(*tmp);
	free(tmp);
	normalize_vector(light_dir);
	intensity = dot_product(*normal, *light_dir);
	free(light_dir);
	if (intensity < 0)
		intensity = 0;
	contribution.r = clamp_color_value(((light->color >> 16) & 0xFF) * intensity * light->intensity);
	contribution.g = clamp_color_value(((light->color >> 8) & 0xFF) * intensity * light->intensity);
	contribution.b = clamp_color_value(((light->color) & 0xFF) * intensity * light->intensity);
	return (contribution);
}

t_color	calculate_illumination(t_vector point, t_vector *normal,
		t_minirt *minirt)
{
	int		i;
	t_color	total_light;
	t_color light_contribution;

	total_light.r = ((minirt->scene->amb_light->color >> 16) & 0xFF) * minirt->scene->amb_light->intensity;
	total_light.g = ((minirt->scene->amb_light->color >> 8) & 0xFF) * minirt->scene->amb_light->intensity;
	total_light.b = (minirt->scene->amb_light->color & 0xFF) * minirt->scene->amb_light->intensity;
	i = 0;
	while (minirt->scene->lights[i])
	{
		light_contribution = check_light_contribution(minirt->scene->lights[i], point, normal, minirt);
		total_light.r = clamp_color_value(total_light.r + light_contribution.r);
		total_light.g = clamp_color_value(total_light.g + light_contribution.g);
		total_light.b = clamp_color_value(total_light.b + light_contribution.b);
		i++;
	}
	return (total_light);
}
