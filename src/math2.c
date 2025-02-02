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

float	dist_cam_viewport(int x, int y, t_minirt *minirt)
{
    float dist;
    float hypotenuse_len;

    dist = dist_from_viewport_origin(x, y, minirt);
    hypotenuse_len = pythagoras(dist, minirt->scene->viewport->d);
	return (hypotenuse_len);
}

void	normalize(t_vector *v)
{
	t_vector	*normalized;
	
	scale_vector(v, 1/norm(*v));
}

void	print_vector(char *name, t_vector v)
{
	printf("%s- x: %f, y: %f, z: %f\n", name, v.x, v.y, v.z);
}

t_ray *send_ray_from_cam(int x, int y, t_minirt *minirt)
{
	float	t;
	t_vector *point_on_viewport;
	t_ray	*ray;
	t_vector	*dir;
	t_vector	*world_up;
	t_vector	*up;
	t_vector	*right;
	t_vector	*cam_vec;
	t_vector	*viewport_origin_to_point;
	float	normalized_x;
	float	normalized_y;
	float	viewport_x;
	float	viewport_y;
	
	normalized_x = ((float)x + 0.5) / WIN_W; //we add 0.5 to cast the ray from the middle of the pixel and not the top left corner, this helps avoiding aliasing artifacts
	normalized_y = ((float)y + 0.5) / WIN_H;
	viewport_x = (normalized_x - 0.5) * minirt->scene->viewport->width;
	viewport_y = (0.5 - normalized_y) * minirt->scene->viewport->height;
	t = dist_cam_viewport(x, y, minirt);
	if (fabs(dot_product(*minirt->scene->camera->orientation, *world_up)) == 1.0)
		world_up = init_vector(0, 1, 0);
	else
		world_up = init_vector(0, 0, 1);
	right = cross_product(*minirt->scene->camera->orientation, *world_up);
	free(world_up);
	up = cross_product(*right, *minirt->scene->camera->orientation);
	scale_vector(right, viewport_x);
	scale_vector(up, viewport_y);
	cam_vec = copy_vector(*minirt->scene->camera->orientation);
	scale_vector(cam_vec, minirt->scene->viewport->d);
	viewport_origin_to_point = sum_vector(*right, *up);
    free(right);
    free(up);
	dir = sum_vector(*cam_vec, *viewport_origin_to_point);
    free(cam_vec);
	normalize(dir);
	free(viewport_origin_to_point);
	ray = init_ray(*minirt->scene->camera->pos, *dir);
    free(dir);
	return (ray);
}
