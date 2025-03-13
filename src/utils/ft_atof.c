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

static float process_integer(const char **str)
{
	float result;

	result = 0.0f;
	while (**str >= '0' && **str <= '9')
	{
		result = (result * 10.0f) + (**str - '0');
		(*str)++;
	}
	return (result);
}

static float process_fractional(const char **str)
{
	float result;
	float decimal_place;

	result = 0.0f;
	decimal_place = 0.1f;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			result += (**str - '0') * decimal_place;
			decimal_place *= 0.1f;
			(*str)++;
		}
	}
	return (result);
}

float ft_atof(const char *str)
{
	float result;
	float sign;

	result = 0.0f;
	sign = 1.0f;
	if (!str)
		return (0.0f);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1.0f;
		str++;
	}
	result = process_integer(&str);
	result += process_fractional(&str);
	return (result * sign);
}
