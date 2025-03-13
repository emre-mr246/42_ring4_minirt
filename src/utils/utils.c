/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:00:22 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 12:48:09 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <fcntl.h>
#include <unistd.h>

int	is_whitespace(char c)
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

int	count_elements(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	strs_equal(char *a, char *b)
{
	if (ft_strncmp(a, b, higher_len(a, b)) == 0)
		return (1);
	return (0);
}
