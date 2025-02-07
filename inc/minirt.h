/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:02:00 by emgul             #+#    #+#             */
/*   Updated: 2024/10/17 19:19:48 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_W 1200
# define WIN_H 800

#define M_PI 3.14159265358979323846

#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1000000.0f

#include <stdio.h>

typedef struct s_vector
{
	float x;
	float y;
	float z;
}	t_vector;

# include "scene.h"

typedef struct s_ray
{
	t_vector	*origin;
	t_vector	*direction;
} t_ray;


typedef struct s_input
{
	int light_count;
    int sphere_count;
    int plane_count;
    int cylinder_count;
	int obj_count;
}	t_input;

typedef struct s_img
{
	void			*ptr;
	char			*data;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_minirt
{
	void *mlx;
	void *win;
	int win_width;
	int win_height;
	t_img img;
	t_scene *scene;
}	t_minirt;

t_minirt *init_minirt();
int ft_exit(char *err, int exit_code, t_minirt *minirt);
int	draw(t_minirt *minirt);
int is_whitespace(char c);
void	parse_input(char *input_file, t_minirt *minirt);
char	**ft_split_charset(char const *s, char *charset);
int	higher_len(char *str1, char *str2);
int	count_elements(char **arr);
void	input_control(char *input_file);
void iter_lines(t_minirt *minirt, char *input_file, int (*f)(char *, void *), void *ptr);
int	strs_equal(char *a, char *b);
int parse_line(char *line, void *scene_data);
float ft_atof(const char *str);
t_vector *init_vector_str(char *str);
t_vector *init_vector(float x, float y, float z);
void fill_scene(t_minirt *minirt, t_input *input);

//init_objs
t_light	*init_light(char **arr);
t_plane	*init_plane(char **arr);
t_sphere	*init_sphere(char **arr);
t_cylinder	*init_cylinder(char **arr);
t_ray *init_ray(t_vector o, t_vector dir);

// intersect
t_vector    *intersect_sphere(t_ray ray, t_sphere sphere);
t_vector *intersect_plane(t_ray ray, t_plane plane);
t_vector *intersect_cylinder(t_ray ray, t_cylinder cylinder);

//math
float	dot_product(t_vector v, t_vector u);
t_vector *cross_product(const t_vector *v, const t_vector *u);
t_vector	*get_point_on_ray(t_ray ray, float t);
t_ray *send_ray_from_cam(int x, int y, t_minirt *minirt);
float discriminant(float a, float b, float c);
float sq(float a);
float solve_eq(float a, float b, float c, t_ray ray);

// vector
t_vector *sum_vector(t_vector v, t_vector u);
void	scale_vector(t_vector *v, float s);
t_vector *subtract_vector(t_vector v, t_vector u);
float	vector_magnitude(t_vector v);
t_vector	*copy_vector(t_vector v);

int	get_color(int x, int y, t_minirt *minirt);

// KEYBOARD AND MOUSE
int	handle_keypress(int key, t_minirt *minirt);
int	handle_mouse(int x, int y, t_minirt *minirt);

// FREE
void free_minirt(t_minirt *minirt);
void free_camera(t_camera *camera);
void free_light(t_light *light);
void free_sphere(t_sphere *sphere);
void free_plane(t_plane *plane);
void free_cylinder(t_cylinder *cylinder);
void	free_array(char **arr);
void free_ray(t_ray *ray);


// debug
void print_vector(char *name, t_vector v);

// color
int clamp_color_value(int value);
int	create_rgb(int red, int green, int blue);
int	parse_color(char *str);

#endif
