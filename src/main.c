/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:28:30 by emgul             #+#    #+#             */
/*   Updated: 2024/10/02 17:16:14 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>

#include "stdlib.h"

int ft_exit(char *err, int exit_code, t_minirt *minirt)
{
    if (exit_code != 0)
        perror(err);
    exit(exit_code);
}

int exit_mlx(t_minirt *minirt)
{
    // free minirt
    exit(0);
    return (0);
}

int main(int ac, char **av)
{
    t_minirt *minirt;

    if (ac != 2)
    {
        ft_putendl_fd("Wrong number of arguments!", 2);
        ft_exit(NULL, 0, minirt);
    }
    parse_input(av[1]);
    minirt = init_minirt();
    if (!minirt)
        return (1);
    draw(minirt);
    //mlx_loop_hook(fdf->mlx_ptr, &, fdf);
	mlx_hook(minirt->win, KeyPress, KeyPressMask, handle_keypress, minirt);
	mlx_hook(minirt->win, DestroyNotify, KeyReleaseMask, exit_mlx, minirt);
	mlx_loop(minirt->mlx);
}