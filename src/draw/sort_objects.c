#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

static float get_object_distance(void *object, int obj_type, t_vector *camera_pos)
{
    if (obj_type == SPHERE)
        return (calculate_distance(camera_pos, ((t_sphere *)object)->origin));
    else if (obj_type == CYLINDER) 
        return (calculate_distance(camera_pos, ((t_cylinder *)object)->origin));
    else if (obj_type == PLANE)
        return (INFINITY);
    return (INFINITY);
}

static void swap_objects(t_minirt *minirt, int j)
{
    void *temp_obj;
    int temp_tag;

    temp_obj = minirt->scene->objects[j];
    minirt->scene->objects[j] = minirt->scene->objects[j + 1];
    minirt->scene->objects[j + 1] = temp_obj;
    temp_tag = minirt->scene->obj_tags[j];
    minirt->scene->obj_tags[j] = minirt->scene->obj_tags[j + 1];
    minirt->scene->obj_tags[j + 1] = temp_tag;
}

void sort_objects_by_distance(t_minirt *minirt)
{
    int i;
    int j;
    float dist1;
    float dist2;
    t_vector *camera_pos;

    camera_pos = minirt->scene->camera->pos;
    i = 0;
    while (minirt->scene->objects[i + 1])
    {
        j = 0;
        while (minirt->scene->objects[j + 1])
        {
            dist1 = get_object_distance(minirt->scene->objects[j], minirt->scene->obj_tags[j], camera_pos);
            dist2 = get_object_distance(minirt->scene->objects[j + 1], minirt->scene->obj_tags[j + 1], camera_pos);
            if (dist1 > dist2)
                swap_objects(minirt, j);
            j++;
        }
        i++;
    }
}
