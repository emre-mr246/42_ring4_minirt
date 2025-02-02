/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:00:22 by emgul             #+#    #+#             */
/*   Updated: 2024/10/18 12:24:37 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

int is_whitespace(char c)
{
    return ((c >= 8 && c <= 13) || c == ' ');
}

int	higher_len(char *str1, char *str2)
{
	int	len1;
	int	len2;

	if (!str1 || !str2)
		return (-1);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

int	count_elements(char **arr)
{
	int i;
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void iter_lines(t_minirt *minirt, char *input_file, int (*f)(char *, void *), void *ptr)
{
	char *line;
    int fd;
    
    fd = open(input_file, O_RDONLY, 0644);
    if (fd == -1)
        ft_exit(input_file, -1, minirt);
    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        ft_exit("Get next line error", -1, minirt);
    }
    while (line)
    {
        if (f(line, ptr) == -1)
			ft_exit("iter_lines error", -1, minirt);
		free(line);
		line = get_next_line(fd);
    }
    free(line);
    close(fd);
}

int	strs_equal(char *a, char *b)
{
	return (ft_strncmp(a, b, higher_len(a, b)) == 0);
}

int	create_rgb(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

int	parse_color(char *str)
{
	char **split;
	int color;

	split = ft_split(str, ',');
	color = create_rgb(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
	free_array(split);
	return (color);
}
