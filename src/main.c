/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:28:30 by emgul             #+#    #+#             */
/*   Updated: 2024/10/17 16:34:49 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include "stdlib.h"

void free_camera(t_camera *camera)
{
    if (camera)
    {
        if (camera->pos)
            free(camera->pos);
        if (camera->orientation)
            free(camera->orientation);
        free(camera);
    }
}

void free_viewport(t_viewport *viewport)
{
    if (viewport)
        free(viewport);
}

void free_light(t_light *light)
{
    if (light)
    {
        if (light->pos)
            free(light->pos);
        free(light);
    }
}

void free_sphere(t_sphere *sphere)
{
    if (sphere)
    {
        if (sphere->origin)
            free(sphere->origin);
        free(sphere);
    }
}

void free_plane(t_plane *plane)
{
    if (plane)
    {
        if (plane->point)
            free(plane->point);
        if (plane->normal)
            free(plane->normal);
        free(plane);
    }
}

void free_cylinder(t_cylinder *cylinder)
{
    if (cylinder)
    {
        if (cylinder->origin)
            free(cylinder->origin);
        if (cylinder->axis)
            free(cylinder->axis);
        free(cylinder);
    }
}

void free_amb_light(t_amb_light *amb_light)
{
    if (amb_light)
        free(amb_light);
}

void free_scene(t_scene *scene)
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
        free(scene);
    }
}

void free_img(t_minirt *minirt)
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

int ft_exit(char *err, int exit_code, t_minirt *minirt)
{
	if (exit_code != 0)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(err, 2);
		free_minirt(minirt);
	}
	exit(exit_code);
}

int exit_mlx(t_minirt *minirt)
{
	free_minirt(minirt);
	exit(0);
	return (0);
}

int main(int ac, char **av)
{
	t_minirt *minirt;

	if (ac != 2)
	{
		ft_putendl_fd("Wrong number of arguments!", 2);
		ft_exit(NULL, 0, minirt);
	}
	input_control(av[1]);
	minirt = init_minirt();
	if (!minirt)
		return (1);
	parse_input(av[1], minirt);
	mlx_loop_hook(minirt->mlx, &draw, minirt);
	mlx_hook(minirt->win, KeyPress, KeyPressMask, handle_keypress, minirt);
	mlx_hook(minirt->win, 06, 1L << 6, handle_mouse, minirt);
	mlx_hook(minirt->win, DestroyNotify, KeyReleaseMask, exit_mlx, minirt);
	mlx_loop(minirt->mlx);
	return (0);
}
