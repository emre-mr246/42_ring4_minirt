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
#include <unistd.h>

static int object_valid(char *str)
{
	if (strs_equal(str, "A") || strs_equal(str, "C") ||
		strs_equal(str, "L") || strs_equal(str, "sp") ||
		strs_equal(str, "cy") || strs_equal(str, "pl"))
		return (1);
	write(2, "Object is not valid: ", 20);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (0);
}

static int arg_count_valid(char **arr)
{
	if (strs_equal(arr[0], "A"))
		return (count_elements(arr) == 3);
	if (strs_equal(arr[0], "C") || strs_equal(arr[0], "L") ||
		strs_equal(arr[0], "sp") || strs_equal(arr[0], "pl"))
		return (count_elements(arr) == 4);
	if (strs_equal(arr[0], "cy"))
		return (count_elements(arr) == 6);
	write(2, "arg count is not valid\n", 23);	
	return (0);
}

static int consecutive_chars(char x, char y)
{
	if ((x == '.' && (y == '.' || y == ',' || y == '-')) ||
		(x == ',' && (y == '.' || y == ',')) ||
		(x == '-' && (y == '.' || y == ',' || y == '-')))
	{
		write(2, "consecutive chars are not valid\n", 32);
		return (1);
	}
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
			if (!ft_isdigit(arr[i][j]) && arr[i][j] != '-' && arr[i][j] != '.' && arr[i][j] != ',')
			{
				write(2, "numbers are not valid\n", 22);
				return (0);
			}
			if (consecutive_chars(arr[i][j], arr[i][j + 1]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int line_checker(char *line, void *ptr)
{
	char **split;
	(void)ptr;

	split = ft_split_charset(line, " \t\n");
	if (!split)
		return (-1);
	if (!object_valid(split[0]) || !arg_count_valid(split) || !numbers_valid(split))
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
