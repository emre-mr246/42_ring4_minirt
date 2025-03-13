/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:46:08 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 12:55:32 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

int	ft_exit(char *err, int exit_code, t_minirt *minirt)
{
	if (exit_code == 0)
		free_minirt(minirt);
	else if (exit_code != 0)
	{
		free_minirt(minirt);
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(err, 2);
	}
	exit(exit_code);
}

int	exit_mlx(t_minirt *minirt)
{
	free_minirt(minirt);
	exit(0);
	return (0);
}
