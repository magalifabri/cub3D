#include "cub3d.h"

void	initialise_variables_part_2(t_cub3d *t)
{
	t->td[0].malloc = 0;
	t->td[1].malloc = 0;
	t->td[2].malloc = 0;
	t->td[3].malloc = 0;
	t->td[4].malloc = 0;
}

void	initialise_variables(t_cub3d *t)
{
	t->save = 0;
	t->error = 0;
	t->fov = 60;
	t->spd = 3;
	t->w = 0;
	t->s = 0;
	t->a = 0;
	t->d = 0;
	t->l_a = 0;
	t->r_a = 0;
	t->mouse_move = 0;
	t->map_w = 0;
	t->p_dir_x = 0;
	t->p_dir_y = 0;
	t->plane_x = 0;
	t->plane_y = 0;
	t->shoot = 0;
	t->p_health = 5;
	t->p_bullets = 5;
	t->p_hit = 0;
	t->malloc_map = 0;
	t->malloc_tex_paths = 0;
	t->malloc_spr = 0;
	t->malloc_td = 1;
	initialise_variables_part_2(t);
}
