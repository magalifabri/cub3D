#include "cub3d.h"

typedef struct	s_check_for_walls_variables
{
	double		y_dest;
	double		x_dest;
    double		y_dif;
    double		x_dif;
    double		step_x;
    double		step_y;
    double		tmp;

}				t_cfwv;

static void		calculate_steps(t_cub3d *t, t_cfwv *c, int s)
{
    if (t->spr[s].y - c->y_dest < 0) // square is below player and needs to travel up (-)
    {
        c->tmp = (c->y_dif / c->x_dif);
        c->step_y = (c->tmp > 1 || c->tmp < -1) ? 1 : c->tmp;
        c->step_y = c->step_y < 0 ? -c->step_y : c->step_y;
    }
    else // square is above player and needs to travel down (+)
    {
        c->tmp = (c->y_dif / c->x_dif);
        c->step_y = (c->tmp > 1 || c->tmp < -1) ? -1 : c->tmp;
        c->step_y = c->step_y > 0 ? -c->step_y : c->step_y;
    }
    if (t->spr[s].x - c->x_dest < 0) // square is to the right of player and needs to go left (-)
    {
        c->tmp = (c->x_dif / c->y_dif);
        c->step_x = (c->tmp > 1 || c->tmp < -1) ? 1 : c->tmp;
        c->step_x = c->step_x < 0 ? -c->step_x : c->step_x;
    }
    else // square is to the left of player and needs to go right (+)
    {
        c->tmp = (c->x_dif / c->y_dif);
        c->step_x = (c->tmp >= 1 || c->tmp < -1) ? -1 : c->tmp;
        c->step_x = c->step_x > 0 ? -c->step_x : c->step_x;
    }
}

static int		in_l_o_s(t_cub3d *t, int s)
{
	t_cfwv c;
	c.y_dest = t->p_y - 0.5;
	c.x_dest = t->p_x - 0.5;
    c.y_dif = t->spr[s].y - c.y_dest;
    c.x_dif = t->spr[s].x - c.x_dest;
	calculate_steps(t, &c, s);
    if (c.y_dif == 0 && c.x_dif == 0)
        return (1);
    while ((int)c.x_dif != 0 || (int)c.y_dif != 0)
    {
        if (t->map[(int)c.y_dest + (int)c.y_dif]
		[(int)c.x_dest + (int)c.x_dif] == '1')
            return (0);
        c.x_dif += c.step_x;
        c.y_dif += c.step_y;
    }
    if (t->map[(int)c.y_dest + (int)c.y_dif]
	[(int)c.x_dest + (int)c.x_dif] == '1')
        return (0);
    return (1);
}

static double	spawn_mobs(t_cub3d *t, int nest)
{
	int sprite;

	sprite = -1;
	while (++sprite < t->sprite_n)
	{
		if (t->spr[sprite].type == '0')
		{
			t->spr[sprite].x = t->spr[nest].x + 1;
			t->spr[sprite].y = t->spr[nest].y;
			t->spr[sprite].type = '3';
			t->spr[sprite].health = 3;
			t->spr[sprite].hit = 0;
			t->spr[sprite].alive = 1;
			t->spr[sprite].mode = 'i';
			t->spr[nest].time_spawn = t->time_now;
			break ;
		}
	}
	return (clock());
}

void			sprite_control(t_cub3d *t, int s)
{
	static double	time_mob_spawn;

	if (t->spr[s].type == '3' && t->spr[s].mode == 'i' && in_l_o_s(t, s))
	{
		t->spr[s].mode = 'm';
		t->spr[s].frame = 0;
	}
	if (t->spr[s].type == '3' && t->spr[s].mode != 'a'&&
	get_distance(t->p_y, t->p_x, (int)t->spr[s].y, (int)t->spr[s].x) < 1.5)
	{
		t->spr[s].mode = 'a';
		t->spr[s].frame = 0;
	}
	if (t->spr[s].type == '3' && t->spr[s].alive && t->spr[s].mode == 'm')
		enemy_pathfinding(t, s);
	if (t->spr[s].type == '5' && t->spr[s].alive
	&& (t->spr[s].time_spawn == 0 
	|| (double)(t->time_now - t->spr[s].time_spawn)
	/ (double)CLOCKS_PER_SEC > 5))
		time_mob_spawn = spawn_mobs(t, s);
}