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
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

int is_whitespace(char c)
{
	return ((c >= 8 && c <= 13) || c == ' ');
}

int higher_len(char *str1, char *str2)
{
	int len1;
	int len2;

	if (!str1 || !str2)
		return (-1);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

int count_elements(char **arr)
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
	while (line)
	{
		if (f(line, ptr) == -1)
		{
			free(line);
			ft_exit("iter_lines error", -1, minirt);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int strs_equal(char *a, char *b)
{
	if (ft_strncmp(a, b, higher_len(a, b)) == 0)
		return (1);
	return (0);
}

