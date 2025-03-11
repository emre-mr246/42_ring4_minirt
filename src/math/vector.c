#include "minirt.h"
#include "libft.h"
#include <math.h>

t_vector *sum_vector(t_vector v, t_vector u)
{
	t_vector *vector;

	vector = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!vector)
		return (NULL);
	vector->x = v.x + u.x;
	vector->y = v.y + u.y;
	vector->z = v.z + u.z;
	return (vector);
}

t_vector *multiply_vector(t_vector vector, float scalar)
{
    t_vector *result;

    result = (t_vector *)malloc(sizeof(t_vector));
    if (!result)
        return (NULL);
    result->x = vector.x * scalar;
    result->y = vector.y * scalar;
    result->z = vector.z * scalar;
    return (result);
}

t_vector *subtract_vector(t_vector v, t_vector u)
{
	t_vector *vector;

	vector = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!vector)
		return (NULL);
	vector->x = v.x - u.x;
	vector->y = v.y - u.y;
	vector->z = v.z - u.z;
	return (vector);
}

t_vector *copy_vector(t_vector v)
{
	t_vector *vector;

	vector = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!vector)
		return (NULL);
	vector->x = v.x;
	vector->y = v.y;
	vector->z = v.z;
	return (vector);
}

void scale_vector(t_vector *v, float s)
{
	v->x *= s;
	v->y *= s;
	v->z *= s;
}

float vector_magnitude(t_vector v)
{
    return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

float vector_magnitude_sq(t_vector v)
{
    return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

void normalize_vector(t_vector *v)
{
    float magnitude;

    magnitude = vector_magnitude(*v);
    if (magnitude > 0.0f)
	{
        v->x /= magnitude;
        v->y /= magnitude;
        v->z /= magnitude;
    }
}

t_vector *normalized_vector(t_vector v)
{
	t_vector *vector;

	vector = copy_vector(v);
	normalize_vector(vector);
	return (vector);
}
