#include "cub3d.h"

typedef struct	s_cast_ray
{
	double		r_dir_x;
	double		r_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
}				t_ray;

static void		make_calculations_3(t_cub3d *t, t_ray *w)
{
	int sprite;

	sprite = -1;
	while (++sprite < t->sprite_n)
	{
		if (t->spr[sprite].y == w->map_y
		&& t->spr[sprite].x == w->map_x)
		{
			t->spr[sprite].health--;
			if (t->spr[sprite].health == 0)
			{
				t->spr[sprite].alive = 0;
				t->map[w->map_y][w->map_x] = '0';
				t->spr[sprite].t_o_d = clock();
			}
			else
				t->spr[sprite].hit = 10;
		}
	}
}

static void		make_calculations_2(t_cub3d *t, t_ray *w)
{
	while (t->map[w->map_y][w->map_x] != '1')
	{
		if (t->map[w->map_y][w->map_x] == '3'
		|| t->map[w->map_y][w->map_x] == '5')
			make_calculations_3(t, w);
		if (w->side_dist_x < w->side_dist_y)
		{
			w->side_dist_x += w->delta_dist_x;
			w->map_x += w->step_x;
		}
		else
		{
			w->side_dist_y += w->delta_dist_y;
			w->map_y += w->step_y;
		}
	}
}

static void		make_calculations_1(t_cub3d *t, t_ray *w)
{
	if (w->r_dir_x < 0)
	{
		w->step_x = -1;
		w->side_dist_x = (t->p_x - w->map_x) * w->delta_dist_x;
	}
	else
	{
		w->step_x = 1;
		w->side_dist_x = (w->map_x + 1.0 - t->p_x) * w->delta_dist_x;
	}
	if (w->r_dir_y < 0)
	{
		w->step_y = -1;
		w->side_dist_y = (t->p_y - w->map_y) * w->delta_dist_y;
	}
	else
	{
		w->step_y = 1;
		w->side_dist_y = (w->map_y + 1.0 - t->p_y) * w->delta_dist_y;
	}
}

void			shoot(t_cub3d *t)
{
	t_ray w;

	t->scrn_x = 2 * (t->win_w / 2) / (double)t->win_w - 1;
	w.r_dir_x = t->p_dir_x + (t->plane_x * t->scrn_x);
	w.r_dir_y = t->p_dir_y + (t->plane_y * t->scrn_x);
	w.map_x = (int)t->p_x;
	w.map_y = (int)t->p_y;
	w.delta_dist_x = fabs(1 / w.r_dir_x);
	w.delta_dist_y = fabs(1 / w.r_dir_y);
	make_calculations_1(t, &w);
	make_calculations_2(t, &w);
}
