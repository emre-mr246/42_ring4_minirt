#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include "stdlib.h"

int ft_exit(char *err, int exit_code, t_minirt *minirt)
{
	if (exit_code == 42)
		free_minirt(minirt);
	else if (exit_code != 0)
	{
		free_minirt(minirt);
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(err, 2);
	}
	exit(exit_code);
}

int exit_mlx(t_minirt *minirt)
{
	free_minirt(minirt);
	exit(0);
	return (0);
}
