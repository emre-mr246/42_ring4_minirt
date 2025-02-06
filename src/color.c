#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include "stdlib.h"

int create_rgb(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

int parse_color(char *str)
{
	char **split;
	int color;

	split = ft_split(str, ',');
	color = create_rgb(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
	free_array(split);
	return (color);
}

int clamp_color_value(int value)
{
	if (value > 255)
		return (255);
	if (value < 0)
		return (0);
	return (value);
}
