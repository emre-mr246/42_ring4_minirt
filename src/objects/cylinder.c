#include "minirt.h"
#include "libft.h"

static t_vector *calculate_cylinder_normal(t_cylinder *cy, t_vector *intersection, t_vector *offset_point)
{
	t_vector *normal;
	t_vector *temp_normal;
	t_vector *proj;

	normal = subtract_vector(*intersection, *cy->origin);
	proj = multiply_vector(*cy->axis, dot_product(*normal, *cy->axis));
	temp_normal = subtract_vector(*normal, *proj);
	free(normal);
	normal = temp_normal;
	normalize_vector(normal);
	free(proj);
	offset_point->x = intersection->x + normal->x * EPSILON;
	offset_point->y = intersection->y + normal->y * EPSILON;
	offset_point->z = intersection->z + normal->z * EPSILON;
	return (normal);
}
int calculate_cylinder_shade(t_cylinder *cy, t_minirt *minirt, t_vector *intersection)
{
	t_vector *normal;
	t_color color;
	t_vector offset_point;
	float intensity;

	normal = calculate_cylinder_normal(cy, intersection, &offset_point);
	intensity = calculate_illumination(offset_point, normal, minirt);
	color.r = clamp_color_value(((cy->color >> 16) & 0xFF) * intensity);
	color.g = clamp_color_value(((cy->color >> 8) & 0xFF) * intensity);
	color.b = clamp_color_value((cy->color & 0xFF) * intensity);
	free(normal);
	return (create_rgb(color.r, color.g, color.b));
}
