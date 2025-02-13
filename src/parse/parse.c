/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:58:30 by emgul             #+#    #+#             */
/*   Updated: 2024/10/08 15:40:53 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

t_input *init_input()
{
	t_input *input;

	input = (t_input *)ft_calloc(sizeof(t_input), 1);
	if (!input)
		ft_exit("input_malloc", -1, NULL);
	return (input);
}

static int count_object(char *line, void *ptr)
{
	int i;
	t_input *input;

	input = (t_input *)ptr;
	i = 0;
	if (!line)
		return (-1);
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (line[i] == 'L' && is_whitespace(line[i + 1]))
		input->light_count++;
	else if (line[i] == 's' && line[i + 1] == 'p' && is_whitespace(line[i + 2]))
		input->sphere_count++;
	else if (line[i] == 'c' && line[i + 1] == 'y' && is_whitespace(line[i + 2]))
		input->cylinder_count++;
	else if (line[i] == 'p' && line[i + 1] == 'l' && is_whitespace(line[i + 2]))
		input->plane_count++;
	return (0);
}

void count_objects(t_input *input, char *input_file)
{
	iter_lines(NULL, input_file, count_object, input);
	input->obj_count = input->light_count + input->sphere_count + input->cylinder_count + input->plane_count;
}

void parse_input(char *input_file, t_minirt *minirt)
{
	t_input *input;
	char *line;

	input = init_input();
	count_objects(input, input_file);
	fill_scene(minirt, input);
	iter_lines(minirt, input_file, parse_line, minirt->scene);
	free(input);
}
