/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:28:30 by emgul             #+#    #+#             */
/*   Updated: 2025/03/13 08:47:02 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <X11/X.h>

int	main(int ac, char **av)
{
	t_minirt	*minirt;

	minirt = NULL;
	if (ac != 2)
	{
		ft_putendl_fd("Wrong number of arguments!", 2);
		ft_exit(NULL, 0, minirt);
	}
	input_control(av[1]);
	minirt = init_minirt();
	if (!minirt)
		return (1);
	parse_input(av[1], minirt);
	mlx_loop_hook(minirt->mlx, &draw, minirt);
	mlx_hook(minirt->win, KeyPress, KeyPressMask, handle_keypress, minirt);
	mlx_hook(minirt->win, DestroyNotify, KeyReleaseMask, exit_mlx, minirt);
	mlx_loop(minirt->mlx);
	return (0);
}
