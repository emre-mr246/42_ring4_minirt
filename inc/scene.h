/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:08:54 by emgul             #+#    #+#             */
/*   Updated: 2024/10/17 19:01:44 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

enum					e_objects
{
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
};

typedef struct s_camera
{
	t_vector	*pos;
	t_vector	*orientation;
	int			fov;
}	t_camera;

typedef struct s_viewport
{
	float	d;
	float width;
	float height;
}	t_viewport;

typedef struct s_amb_light
{
	int			color;
	float		intensity;
}				t_amb_light;

typedef struct s_light
{
	t_vector *pos;
	float intensity;
}	t_light;

typedef struct s_sphere
{
	t_vector	*origin;
	float		radius;
	int			color;
}				t_sphere;

typedef struct s_plane
{
	t_vector	*point;
	t_vector	*normal;
	int			color;

}				t_plane;

typedef struct s_cylinder
{
	t_vector	*origin;
	t_vector	*axis;
	float		radius;
	float		height;
	int			color;
}				t_cylinder;

typedef struct s_scene
{
	t_camera	*camera;
	t_viewport	*viewport;
	t_amb_light	*amb_light;
	t_light		**lights;
	void		**objects;
	int			*obj_tags;
}	t_scene;

#endif