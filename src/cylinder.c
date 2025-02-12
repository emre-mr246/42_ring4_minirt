#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

static t_vector *calculate_cylinder_normal(t_cylinder *cy, t_vector *intersection, t_vector *offset_point)
{
    t_vector *normal;
	t_vector *proj;
    
    normal = subtract_vector(*intersection, *cy->origin);
    proj = multiply_vector(*cy->axis, dot_product(*normal, *cy->axis));
    normal = subtract_vector(*normal, *proj);
    normalize_vector(normal);
    free(proj);
    offset_point->x = intersection->x + normal->x * EPSILON;
    offset_point->y = intersection->y + normal->y * EPSILON;
    offset_point->z = intersection->z + normal->z * EPSILON;
    return (normal);
}

static int calculate_cylinder_shade(t_cylinder *cy, t_ray *ray, t_minirt *minirt, t_vector *intersection)
{
    t_vector *normal;
    t_color color;
    float intensity;
    t_vector offset_point;

    normal = calculate_cylinder_normal(cy, intersection, &offset_point);
    intensity = calculate_illumination(offset_point, normal, minirt);
    color.r = clamp_color_value(((cy->color >> 16) & 0xFF) * intensity);
    color.g = clamp_color_value(((cy->color >> 8) & 0xFF) * intensity);
    color.b = clamp_color_value((cy->color & 0xFF) * intensity);
    free(normal);
    return (create_rgb(color.r, color.g, color.b));
}

int check_cylinder_intersection(t_ray *ray, t_minirt *minirt)
{
    int i;
    t_cylinder *cylinder;
    t_vector *intersection;
    int color;

    i = 0;
    while (minirt->scene->objects[i])
    {
        if (minirt->scene->obj_tags[i] == CYLINDER)
        {
            cylinder = (t_cylinder *)minirt->scene->objects[i];
            intersection = intersect_cylinder(*ray, *cylinder);
            if (intersection)
            {
                color = calculate_cylinder_shade(cylinder, ray, minirt, intersection);
                free(intersection);
                return (color);
            }
        }
        // ışığı küre şeklinde görmek için debug amaçlı
        if (minirt->scene->obj_tags[i] == LIGHT)
        {
            t_sphere *sp = malloc(sizeof(t_sphere));
            sp->origin = minirt->scene->lights[0]->pos;
            sp->radius = 0.5;
            if (intersect_sphere(*ray, *sp))
                return (1);
            free(sp);
        }
        i++;
    }
    return (0);
}
