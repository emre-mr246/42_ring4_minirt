#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

static t_vector *get_intersection(t_ray *ray, void *object, int obj_type)
{
    t_vector *intersection;

    intersection = NULL;
    if (obj_type == SPHERE)
        intersection = intersect_sphere(*ray, *(t_sphere *)object);
    else if (obj_type == CYLINDER)
        intersection = intersect_cylinder(*ray, *(t_cylinder *)object);
    else if (obj_type == PLANE)
        intersection = intersect_plane(*ray, *(t_plane *)object);
    return (intersection);
}

static int check_object_intersection(t_ray *ray, void *object, int obj_type, t_minirt *minirt)
{
    t_vector *intersection;
    int color;

    color = 0;
    intersection = get_intersection(ray, object, obj_type);
    if (intersection)
    {
        if (obj_type == SPHERE)
            color = calculate_sphere_shade((t_sphere *)object, ray, minirt, intersection);
        else if (obj_type == CYLINDER)
            color = calculate_cylinder_shade((t_cylinder *)object, ray, minirt, intersection);
        else if (obj_type == PLANE)
            color = calculate_plane_shade((t_plane *)object, ray, minirt, intersection);
        free(intersection);
    }
    return (color);
}

int check_intersections(t_ray *ray, t_minirt *minirt)
{
    int i;
    int color;

    sort_objects_by_distance(minirt);
    i = 0;
    while (minirt->scene->objects[i])
    {
        color = check_object_intersection(ray, minirt->scene->objects[i],
            minirt->scene->obj_tags[i], minirt);
        if (color != 0)
            return (color);
        i++;
    }
    return (0);
}