/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:48:35 by emgul             #+#    #+#             */
/*   Updated: 2025/03/17 19:23:41 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <fcntl.h>
#include <unistd.h>

static int	is_valid_line(char *line)
{
	return (!(ft_strncmp(line, "", 1) == 0 || ft_strncmp(line, "\n", 1) == 0
			|| ft_strncmp(line, "\0", 1) == 0 || ft_strncmp(line, "\t",
				1) == 0));
}

static void	process_line(char *line, int (*f)(char *, void *), void *ptr,
		t_minirt *minirt)
{
	if (f(line, ptr) == -1)
	{
		free(line);
		ft_exit("iter_lines error", -1, minirt);
	}
	free(line);
}

int	is_rt(char *s)
{
	int len;

	len = ft_strlen(s);
	return (s[len - 3] == '.' && s[len - 2] == 'r' && s[len - 1] == 't');
}

void	iter_lines(t_minirt *minirt, char *input_file, int (*f)(char *, void *),
		void *ptr)
{
	char	*line;
	int		fd;

	if (!is_rt(input_file))
		ft_exit("Input file does not end with rt", 1, minirt);
	fd = open(input_file, O_RDONLY, 0644);
	if (fd == -1)
		ft_exit(input_file, -1, minirt);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_valid_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		process_line(line, f, ptr, minirt);
		line = get_next_line(fd);
	}
	close(fd);
}
