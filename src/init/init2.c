/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:15:37 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 09:15:39 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <math.h>

t_vector	*init_vector_str(char *str, float max, float min)
{
	char		**split;
	t_vector	*v;

	if (!str)
		return (NULL);
	v = (t_vector *)ft_calloc(sizeof(t_vector), 1);
	if (!v)
		return (NULL);
	split = ft_split(str, ',');
	v->x = fmin(fmax(ft_atof(split[0]), min), max);
	v->y = fmin(fmax(ft_atof(split[1]), min), max);
	v->z = fmin(fmax(ft_atof(split[2]), min), max);
	free_array(split);
	return (v);
}
