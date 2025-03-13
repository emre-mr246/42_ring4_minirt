#include "libft.h"
#include "minirt.h"
#include "mlx.h"

t_vector	*init_vector_str(char *str)
{
	char		**split;
	t_vector	*v;

	if (!str)
		return (NULL);
	v = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!v)
		return (NULL);
	split = ft_split(str, ',');
	v->x = ft_atof(split[0]);
	v->y = ft_atof(split[1]);
	v->z = ft_atof(split[2]);
	free_array(split);
	return (v);
}
