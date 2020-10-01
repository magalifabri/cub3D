#include "cub3d.h"

void    ft_init(cub3d *t)
{
	t->fov = 60;
	t->game = 1;
	t->spd = 3;
	t->w = 0;
	t->s = 0;
	t->a = 0;
	t->d = 0;
	t->l_a = 0;
	t->r_a = 0;
	t->map_w = 0;
}
