/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:08:16 by emgul             #+#    #+#             */
/*   Updated: 2024/10/17 19:44:02 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

// float dist_cam_viewport(int x, int y, t_minirt *minirt)
// {
// 	float dist;
// 	float hypotenuse_len;

// 	dist = dist_from_viewport_origin(x, y, minirt);
// 	hypotenuse_len = pythagoras(dist, minirt->scene->viewport->d);
// 	return (hypotenuse_len);
// }

// void normalize(t_vector *v)
// {
// 	scale_vector(v, 1 / norm(*v));
// }

float pythagoras(float a, float b)
{
	return sqrt(a * a + b * b);
}

float dist_from_viewport_origin(int x, int y, t_minirt *minirt)
{
	t_viewport *viewport;
	int origin_x;
	int origin_y;

	viewport = minirt->scene->viewport;
	origin_x = viewport->width / 2;
	origin_y = viewport->height / 2;
	return (pythagoras(fabsf((float)x - (float)origin_x), fabsf((float)y - (float)origin_y)));
}


t_vector *scale_and_normalize(t_vector *v, float scalar)
{
	t_vector *scaled_vector;

	scaled_vector = copy_vector(*v);
	scale_vector(scaled_vector, scalar);
	return scaled_vector;
}

void calculate_right_up_vectors(t_vector *orientation, t_vector **right, t_vector **up)
{
	t_vector *world_up;

	world_up = init_vector(0, 1, 0);
	*right = cross_product(orientation, world_up);
	*up = cross_product(*right, orientation);
	free(world_up);
}

t_vector *get_ray_direction(float viewport_x, float viewport_y, t_vector *cam_orientation, t_vector *right, t_vector *up)
{
	t_vector *scaled_right;
	t_vector *scaled_up;
	t_vector *cam_vec;
	t_vector *viewport_origin_to_point;
	t_vector *dir;

	scaled_right = scale_and_normalize(right, viewport_x);
	scaled_up = scale_and_normalize(up, viewport_y);
	cam_vec = scale_and_normalize(cam_orientation, 4.0f);
	viewport_origin_to_point = sum_vector(*scaled_right, *scaled_up);
	dir = sum_vector(*cam_vec, *viewport_origin_to_point);
	// normalize(dir);
	free(scaled_right);
	free(scaled_up);
	free(cam_vec);
	free(viewport_origin_to_point);
	return (dir);
}

void calculate_viewport_coordinates(int x, int y, t_minirt *minirt, float *viewport_x, float *viewport_y)
{
	float normalized_x;
	float normalized_y;

 	normalized_x = ((float)x + 0.5f) / WIN_W;
	normalized_y = ((float)y + 0.5f) / WIN_H;
	*viewport_x = (normalized_x - 0.5f) * minirt->scene->viewport->width;
	*viewport_y = (0.5f - normalized_y) * minirt->scene->viewport->height;
}

t_vector *calculate_ray_direction(int x, int y, t_minirt *minirt)
{
	float viewport_x;
	float viewport_y;
	t_vector *right;
	t_vector *up;
	t_vector *dir;

	calculate_viewport_coordinates(x, y, minirt, &viewport_x, &viewport_y);
	calculate_right_up_vectors(minirt->scene->camera->orientation, &right, &up);
	dir = get_ray_direction(viewport_x, viewport_y, minirt->scene->camera->orientation, right, up);
	free(right);
	free(up);
	return (dir);
}

t_ray *send_ray_from_cam(int x, int y, t_minirt *minirt)
{
	t_vector *direction;
	t_ray *ray;

	direction = calculate_ray_direction(x, y, minirt);
	ray = init_ray(*minirt->scene->camera->pos, *direction);
	free(direction);
	return (ray);
}
