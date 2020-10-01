#include "cub3d.h"

typedef struct	s_find_path_variables
{
	int			current_y;
	int			current_x;
	int			i;
	int			check;
	int			front_of_list;
}				t_fpv;

static void	check_north(t_cub3d *t, t_fpv *f)
{
	if (!obstacle(t->map[f->current_y - 1][f->current_x]))
	{
		// check if adjacent north square is on the list
		f->check = f->front_of_list + 1;
		while (--f->check >= 0 && !(t->l[f->check].y == f->current_y - 1
		&& t->l[f->check].x == f->current_x))
		{
			if (f->check == 0) // if f->check reaches 0, that means the coords aren't on the list
			{
				// it has not been visited, 
				t->l[++f->front_of_list].y = f->current_y - 1;
				t->l[f->front_of_list].x = f->current_x;
				t->l[f->front_of_list].direction_of_origin = 's';
			}
		}
	}
}

static void	check_south(t_cub3d *t, t_fpv *f)
{
	if (!obstacle(t->map[f->current_y + 1][f->current_x])) // check adjacent south square
	{
		f->check = f->front_of_list + 1;
		while (--f->check >= 0 && !(t->l[f->check].y == f->current_y + 1
		&& t->l[f->check].x == f->current_x))
		{
			if (f->check == 0)
			{
				t->l[++f->front_of_list].y = f->current_y + 1;
				t->l[f->front_of_list].x = f->current_x;
				t->l[f->front_of_list].direction_of_origin = 'n';
			}
		}
	}
}

static void	check_west(t_cub3d *t, t_fpv *f)
{
	if (!obstacle(t->map[f->current_y][f->current_x - 1]))
	{
		f->check = f->front_of_list + 1;
		while (--f->check >= 0 && !(t->l[f->check].y == f->current_y
		&& t->l[f->check].x == f->current_x - 1))
		{
			if (f->check == 0)
			{
				t->l[++f->front_of_list].y = f->current_y;
				t->l[f->front_of_list].x = f->current_x - 1;
				t->l[f->front_of_list].direction_of_origin = 'e';
			}
		}
	}
}

static void	check_east(t_cub3d *t, t_fpv *f)
{
	if (!obstacle(t->map[f->current_y][f->current_x + 1]))
	{
		f->check = f->front_of_list + 1;
		while (--f->check >= 0 && !(t->l[f->check].y == f->current_y
		&& t->l[f->check].x == f->current_x + 1))
		{
			if (f->check == 0)
			{
				t->l[++f->front_of_list].y = f->current_y;
				t->l[f->front_of_list].x = f->current_x + 1;
				t->l[f->front_of_list].direction_of_origin = 'w';
			}
		}
	}
}

void		enemy_pathfinding(t_cub3d *t, int s)
{
	t_fpv f;

	f.i = 0;
	if (!(t->l = malloc(sizeof(t_visited_squares) * 300)))
		exit_cub3d(t);
	t->l[f.i].y = t->p_y;
	t->l[f.i].x = t->p_x;
	f.front_of_list = 0;
	// check if searched object is found in current location
	while (!(t->l[f.i].y == (int)t->spr[s].y
	&& t->l[f.i].x == (int)t->spr[s].x))
	{
		f.current_y = t->l[f.i].y;
		f.current_x = t->l[f.i].x;
		check_north(t, &f);
		check_south(t, &f);
		check_west(t, &f);
		check_east(t, &f);
		f.i++;
	}
	t->path_steps = f.i;
	move_enemy(t, s);
	free(t->l);
}
