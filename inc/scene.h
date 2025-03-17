/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:08:54 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 10:46:50 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# define M_PI 3.14159265358979323846

# define RAY_T_MIN 0.0001f
# define RAY_T_MAX 200.0f

# define MAX_RENDER_DIST 10.0f
# define MIN_RENDER_DIST 0.1f

# define MAX_POS 1000
# define MIN_POS -1000

# define MAX_RADIUS 1000

# define EPSILON 0.001f

enum			e_objects
{
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
};

typedef struct s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct s_camera
{
	t_vector	*pos;
	t_vector	*orientation;
	int			fov;
}				t_camera;

typedef struct s_viewport
{
	float		d;
	float		width;
	float		height;
}				t_viewport;

typedef struct s_amb_light
{
	int			color;
	float		intensity;
}				t_amb_light;

typedef struct s_light
{
	t_vector	*pos;
	float		intensity;
	int			color;
}				t_light;

typedef struct s_sphere
{
	t_vector	*origin;
	float		radius;
	int			color;
	float		distance;
}				t_sphere;

typedef struct s_plane
{
	t_vector	*point;
	t_vector	*normal;
	int			color;
	float		distance;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	*origin;
	t_vector	*axis;
	float		radius;
	float		height;
	int			color;
	float		distance;
}				t_cylinder;

typedef struct s_scene
{
	t_camera	*camera;
	t_viewport	*viewport;
	t_amb_light	*amb_light;
	t_light		**lights;
	void		**objects;
	int			*obj_tags;
	int			object_count;
}				t_scene;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_viewport_coord
{
	double		x;
	double		y;
}				t_viewport_coord;

typedef struct s_ray
{
	t_vector	*origin;
	t_vector	*direction;
}				t_ray;

#endif