#include "cub3d.h"

static int	get_frame_spider_attack(t_cub3d *t, int i)
{
	if ((double)(t->time_now - t->spr[i].time_frame_swp)
	/ (double)CLOCKS_PER_SEC > 0.1)
	{
		t->spr[i].frame++;
		t->spr[i].time_frame_swp = t->time_now;
	}
	if (t->spr[i].frame > 4)
		t->spr[i].frame = 0;
	// switch back to walking if player moved away
	if (t->spr[i].frame == 0
	&& get_distance(t->p_y, t->p_x, (int)t->spr[i].y, (int)t->spr[i].x) > 1.5)
	{
		t->spr[i].mode = 'm';
		t->spr[i].frame = 0;
	}
	// damage player if player is within range at the striking frame
	if (t->spr[i].frame == 3
	&& get_distance(t->p_y, t->p_x, (int)t->spr[i].y, (int)t->spr[i].x) < 1.5
	&& (t->p_hit == 0 || (double)(t->time_now - t->p_hit)
	/ (double)CLOCKS_PER_SEC > 0.1))
	{
		t->p_health--;
		t->p_hit = clock();
	}
	return (t->spr[i].frame + 29);
}

static int	get_frame_bullets(t_cub3d *t, int i)
{
	if ((double)(t->time_now - t->spr[i].time_frame_swp)
	/ (double)CLOCKS_PER_SEC > 0.1)
	{
		t->spr[i].frame++;
		t->spr[i].time_frame_swp = t->time_now;
	}
	if (t->spr[i].frame > 3)
		t->spr[i].frame = 0;
	if (get_distance(t->p_y, t->p_x, (int)t->spr[i].y, (int)t->spr[i].x) < 1.1)
	{
		t->p_bullets += 2;
		t->map[(int)t->spr[i].y][(int)t->spr[i].x] = '0';
		t->spr[i].type = '0';
	}
	return (t->spr[i].frame + 39);
}

static int	get_frame_spider_walk(t_cub3d *t, int i)
{
	if ((double)(t->time_now - t->spr[i].time_frame_swp)
	/ (double)CLOCKS_PER_SEC > 0.05)
	{
		t->spr[i].frame++;
		t->spr[i].time_frame_swp = t->time_now;
	}
	if (t->spr[i].frame > 5)
		t->spr[i].frame = 0;
	return (t->spr[i].frame + 23);
}

int			get_sprite_frame(t_cub3d *t, int i)
{
	// turn dead spiders into bullets after death animation has played
	if (t->spr[i].type == '3'
	&& !t->spr[i].alive && (double)(t->time_now - t->spr[i].t_o_d)
	/ (double)CLOCKS_PER_SEC > 0.1 && t->spr[i].type != '0')
	{
		t->map[(int)t->spr[i].y][(int)t->spr[i].x] = '4';
		t->spr[i].type = '4';
	}
	if (t->spr[i].hit > 0)
		t->spr[i].hit--;
	if (t->spr[i].type == '2')
		return (4);
	if (t->spr[i].type == '5')
		return (43);
	if (t->spr[i].type == '4')
		return (get_frame_bullets(t, i));
	if (!t->spr[i].alive)
		return (21);
	else if (t->spr[i].mode == 'm')
		return (get_frame_spider_walk(t, i));
	else if (t->spr[i].mode == 'a')
		return (get_frame_spider_attack(t, i));
	else
		return (23);
}
