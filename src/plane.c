#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

static t_vector *calculate_plane_normal(t_plane *pl, t_vector *intersection, t_vector *offset_point)
{
    t_vector *normal;
    
    normal = copy_vector(*pl->normal);
    normalize_vector(normal);
    offset_point->x = intersection->x + normal->x * EPSILON;
    offset_point->y = intersection->y + normal->y * EPSILON;
    offset_point->z = intersection->z + normal->z * EPSILON;
    return (normal);
}

static int calculate_plane_shade(t_plane *pl, t_ray *ray, t_minirt *minirt, t_vector *intersection)
{
    t_vector *normal;
    t_color color;
    float intensity;
    t_vector offset_point;

    normal = calculate_plane_normal(pl, intersection, &offset_point);
    intensity = calculate_illumination(offset_point, normal, minirt);
    color.r = clamp_color_value(((pl->color >> 16) & 0xFF) * intensity);
    color.g = clamp_color_value(((pl->color >> 8) & 0xFF) * intensity);
    color.b = clamp_color_value((pl->color & 0xFF) * intensity);
    free(normal);
    return (create_rgb(color.r, color.g, color.b));
}

int check_plane_intersection(t_ray *ray, t_minirt *minirt)
{
    int i;
    t_plane *plane;
    t_vector *intersection;
    int color;

    i = 0;
    while (minirt->scene->objects[i])
    {
        if (minirt->scene->obj_tags[i] == PLANE)
        {
            plane = (t_plane *)minirt->scene->objects[i];
            intersection = intersect_plane(*ray, *plane);
            if (intersection)
            {
                color = calculate_plane_shade(plane, ray, minirt, intersection);
                free(intersection);
                return (color);
            }
        }
        i++;
    }
    return (0);
}