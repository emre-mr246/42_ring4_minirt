/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:42:15 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 10:50:55 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include "scene.h"

# define WIN_W 900
# define WIN_H 600

typedef struct s_input
{
	int			light_count;
	int			sphere_count;
	int			plane_count;
	int			cylinder_count;
	int			obj_count;
}				t_input;

typedef struct s_img
{
	void		*ptr;
	char		*data;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_minirt
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	t_img		img;
	t_scene		*scene;
}				t_minirt;

t_minirt		*init_minirt(void);
int				ft_exit(char *err, int exit_code, t_minirt *minirt);
int				exit_mlx(t_minirt *minirt);
int				draw(t_minirt *minirt);
int				is_whitespace(char c);
void			parse_input(char *input_file, t_minirt *minirt);
char			**ft_split_charset(char const *s, char *charset);
int				higher_len(char *str1, char *str2);
int				count_elements(char **arr);
void			input_control(char *input_file);
void			iter_lines(t_minirt *minirt, char *input_file, int (*f)(char *,
						void *), void *ptr);
int				strs_equal(char *a, char *b);
int				parse_line(char *line, void *scene_data);
float			ft_atof(const char *str);
t_vector		*init_vector_str(char *str);
t_vector		*init_vector(float x, float y, float z);
void			fill_scene(t_minirt *minirt, t_input *input);

// init_objs
void			init_light(t_scene *scene, char **arr);
t_plane			*init_plane(char **arr);
t_sphere		*init_sphere(char **arr);
t_cylinder		*init_cylinder(char **arr);
t_ray			*init_ray(t_vector o, t_vector dir);

// intersect
t_vector		*intersect_sphere(t_ray ray, t_sphere sphere);
t_vector		*intersect_plane(t_ray ray, t_plane plane);
t_vector		*intersect_cylinder(t_ray ray, t_cylinder cylinder);

// math
float			dot_product(t_vector v, t_vector u);
t_vector		*cross_product(const t_vector *v, const t_vector *u);
t_vector		*get_point_on_ray(t_ray ray, float t);
t_ray			*send_ray_from_cam(int x, int y, t_minirt *minirt);
float			discriminant(float a, float b, float c);
float			sq(float a);
float			solve_eq(float a, float b, float c);
float			calculate_distance(t_vector *a, t_vector *b);

// vector
t_vector		*sum_vector(t_vector v, t_vector u);
void			scale_vector(t_vector *v, float s);
t_vector		*subtract_vector(t_vector v, t_vector u);
float			vector_magnitude(t_vector v);
t_vector		*copy_vector(t_vector v);
void			normalize_vector(t_vector *v);
t_vector		*multiply_vector(t_vector vector, float scalar);

// KEYBOARD AND MOUSE
int				handle_keypress(int key, t_minirt *minirt);

// FREE
void			free_minirt(t_minirt *minirt);
void			free_camera(t_camera *camera);
void			free_light(t_light *light);
void			free_sphere(t_sphere *sphere);
void			free_plane(t_plane *plane);
void			free_cylinder(t_cylinder *cylinder);
void			free_array(char **arr);
void			free_ray(t_ray *ray);

// color
int				clamp_color_value(int value);
int				create_rgb(int red, int green, int blue);
int				parse_color(char *str);
t_color			apply_intensity(t_color color, float intensity);

// light
float			calculate_light_intensity(t_vector *intersection,
					t_vector *normal, t_minirt *minirt, t_light *light);
int				is_in_shadow(t_vector *point, t_light *light, t_minirt *minirt);
float			check_light_contribution(t_light *light, t_vector offset_point,
					t_vector *normal, t_minirt *minirt);
float			calculate_illumination(t_vector offset_point, t_vector *normal,
					t_minirt *minirt);

float			vector_len(t_vector *v);

int				plane_shade(t_plane *pl, t_ray *ray, t_minirt *minirt,
					t_vector *intersection);
int				cylinder_shade(t_cylinder *cy, t_minirt *minirt,
					t_vector *intersection);
int				sphere_shade(t_sphere *sp, t_minirt *minirt,
					t_vector *intersection);

// sort_objects
void			sort_objects_by_distance(t_minirt *minirt);

// check_intersections
int				check_intersections(t_ray *ray, t_minirt *minirt);

// math3
int				clamp(int number, int min, int max);

int				plane_shade(t_plane *plane, t_ray *ray,
					t_minirt *minirt, t_vector *intersection);

t_vector		*get_intersection(t_ray *ray, void *object, int obj_type);
int				check_intersection_and_distance(t_ray *ray, t_minirt *minirt,
					int i, float *distance);
void			reset_camera(t_minirt *minirt);

void			input_control(char *input_file);
int				line_checker(char *line, void *ptr);

void			free_array(char **arr);
#endif
