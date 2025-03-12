/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:57:22 by emgul             #+#    #+#             */
/*   Updated: 2024/10/03 14:23:33 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static int object_valid(char *str)
{
	if (strs_equal(str, "A"))
		return (1);
	if (strs_equal(str, "C"))
		return (1);
	if (strs_equal(str, "L"))
		return (1);
	if (strs_equal(str, "sp"))
		return (1);
	if (strs_equal(str, "cy"))
		return (1);
	if (strs_equal(str, "pl"))
		return (1);
	return (0);
}

static int arg_count_valid(char **arr)
{
	if (strs_equal(arr[0], "A"))
		return (count_elements(arr) == 3);
	if (strs_equal(arr[0], "C"))
		return (count_elements(arr) == 4);
	if (strs_equal(arr[0], "L"))
		return (count_elements(arr) == 4);
	if (strs_equal(arr[0], "sp"))
		return (count_elements(arr) == 4);
	if (strs_equal(arr[0], "pl"))
		return (count_elements(arr) == 4);
	if (strs_equal(arr[0], "cy"))
		return (count_elements(arr) == 6);
	return (0);
}

static int consecutive_chars(char x, char y)
{
	if (x == '.' && (y == '.' || y == ',' || y == '-'))
		return (1);
	if (x == ',' && (y == '.' || y == ','))
		return (1);
	if (x == '-' && (y == '.' || y == ',' || y == '-'))
		return (1);
	return (0);
}

static int numbers_valid(char **arr)
{
	int i;
	int j;

	i = 1;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (ft_isdigit(arr[i][j]) && arr[i][j] == '-' && arr[i][j] == '.' && arr[i][j] == ',')
				return (0);
			if (consecutive_chars(arr[i][j], arr[i][j + 1]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int color_valid(char **arr)
{
	char *col;
	char **split;
	int i;

	if (strs_equal(arr[0], "A"))
		col = arr[2];
	else if (strs_equal(arr[0], "L") || strs_equal(arr[0], "pl") || strs_equal(arr[0], "sp"))
		col = arr[3];
	else if (strs_equal(arr[0], "cy"))
		col = arr[5];
	else
		return (1);
	split = ft_split(col, ',');
	i = 0;
	while (split && split[i])
	{
		if (ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 255)
			return (0);
		i++;
	}
	free_array(split);
	return (1);
}
#include <stdio.h>
int line_checker(char *line, void *ptr)
{
	char **split;
	(void)ptr;

	split = ft_split_charset(line, " \t");
	if (!split)
		return (-1);
	
	if (!object_valid(split[0]) || !arg_count_valid(split) || !numbers_valid(split) || !color_valid(split))
	{
		free_array(split);
		return (-1);
	}
	free_array(split);
	return (0);
}

void input_control(char *input_file)
{
	iter_lines(NULL, input_file, line_checker, NULL);
}
