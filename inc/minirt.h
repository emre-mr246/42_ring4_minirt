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

#include <stdio.h>

typedef struct s_vector
{
	float x;
	float y;
	float z;
}	t_vector;

typedef struct s_ray
{
	t_vector	*origin;
	t_vector	*direction;
} t_ray;

# include "scene.h"

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
int	handle_keypress(int key, t_minirt *minirt);
void	draw(t_minirt *minirt);
int is_whitespace(char c);
void	parse_input(char *input_file, t_minirt *minirt);
char	**ft_split_charset(char const *s, char *charset);
int	higher_len(char *str1, char *str2);
void	free_array(char **arr);
int	count_elements(char **arr);
void	input_control(char *input_file);
void iter_lines(t_minirt *minirt, char *input_file, int (*f)(char *, void *), void *ptr);
int	strs_equal(char *a, char *b);
int parse_line(char *line, t_scene *scene);
int	create_rgb(int red, int green, int blue);
int	parse_color(char *str);
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


//math
float	dot_product(t_vector v, t_vector u);
t_vector *cross_product(t_vector v, t_vector u);
t_vector *sum_vector(t_vector v, t_vector u);
void	scale_vector(t_vector *v, float s);
t_vector	*get_point_on_ray(t_ray ray, float t);
t_vector *subtract_vector(t_vector v, t_vector u);
t_vector    *intersect_sphere(t_ray ray, t_sphere sphere);
t_vector    *intersect_plane(t_ray ray, t_plane plane);
t_ray *send_ray_from_cam(int x, int y, t_minirt *minirt);
float	norm(t_vector v);
t_vector	*copy_vector(t_vector v);

int	get_color(int x, int y, t_minirt *minirt);

void	print_vector(char *name, t_vector v);
#endif