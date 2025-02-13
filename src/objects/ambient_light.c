#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

int calculate_ambient_light(int color, t_amb_light *amb_light)
{
	int r;
	int g;
	int b;

	if (!amb_light)
		return (color);
	r = ((color >> 16) & 0xFF) * amb_light->intensity;
	g = ((color >> 8) & 0xFF) * amb_light->intensity;
	b = (color & 0xFF) * amb_light->intensity;
	r = clamp_color_value(r);
	g = clamp_color_value(g);
	b = clamp_color_value(b);
	return (create_rgb(r, g, b));
}