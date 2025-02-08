#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

void print_vector(char *name, t_vector v)
{
	printf("%s x: %f, y: %f, z: %f\n", name, v.x, v.y, v.z);
}
