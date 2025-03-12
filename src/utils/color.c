#include "minirt.h"
#include "libft.h"

int clamp_color_value(int value)
{
    if (value < 0)
        return (0);
    if (value > 255)
        return (255);
    return (value);
}

int create_rgb(int red, int green, int blue)
{
    return ((red << 16) | (green << 8) | blue);
}

int parse_color(char *str)
{
    char **colors;
    int r;
    int g;
    int b;

    colors = ft_split_charset(str, ",");
    if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
    {
        if (colors)
            free_array(colors);
        return (0);
    }
    r = clamp(ft_atoi(colors[0]), 0, 255);
	g = clamp(ft_atoi(colors[1]), 0, 255);
	b = clamp(ft_atoi(colors[2]), 0, 255);
    free_array(colors);
    return (create_rgb(r, g, b));
}

t_color apply_intensity(t_color color, float intensity)
{
    t_color result;
    
    result.r = clamp_color_value((int)(color.r * intensity));
    result.g = clamp_color_value((int)(color.g * intensity));
    result.b = clamp_color_value((int)(color.b * intensity));
    return (result);
}
