
// int fractol_kure_kodu(t_sphere *sp, t_ray *ray)
// {
// 	t_vector *normal;
// 	t_vector *light_dir;
// 	float intensity;
// 	int color;

// 	normal = subtract_vector(*intersect_sphere(*ray, *sp), *sp->origin);
// 	normalize_vector(normal);
// 	light_dir = subtract_vector(*sp->origin, *ray->origin);
// 	normalize_vector(light_dir);
// 	intensity = dot_product(*normal, *light_dir);
// 	color = sp->color * intensity;
// 	free(normal);
// 	free(light_dir);
// 	return (color);
// }