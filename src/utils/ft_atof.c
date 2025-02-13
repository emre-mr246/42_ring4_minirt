/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:39:00 by emgul             #+#    #+#             */
/*   Updated: 2024/10/03 14:39:24 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

float ft_atof(const char *str)
{
	float result = 0.0f;
	float sign = 1.0f;
	float decimal_place = 1.0f;

	if (!str)
		return 0.0f;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			sign = -1.0f;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10.0f) + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			decimal_place *= 0.1f;
			result += (*str - '0') * decimal_place;
			str++;
		}
	}
	return (result * sign);
}
