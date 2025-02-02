/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:07:32 by emgul             #+#    #+#             */
/*   Updated: 2024/10/17 16:16:46 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>

int	handle_keypress(int key, t_minirt *minirt)
{
    if (key == 65307)
        ft_exit(NULL, 0, minirt);
	return (0);
}
