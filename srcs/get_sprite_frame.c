/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprite_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 09:22:47 by Magali            #+#    #+#             */
/*   Updated: 2020/05/01 21:32:38 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (t->spr[i].frame == 0
	&& get_distance(t->p_y, t->p_x, (int)t->spr[i].y, (int)t->spr[i].x) > 1.5)
	{
		t->spr[i].mode = 'm';
		t->spr[i].frame = 0;
	}
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
		system("afplay -v 0.10 audio/reload.mp3 & exit");
		t->p_bullets = (t->p_bullets >= 18) ? 20 : t->p_bullets + 2;
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
	if ((t->spr[i].type == '3' || t->spr[i].type == '5')
	&& !t->spr[i].alive && (double)(t->time_now - t->spr[i].t_o_d)
	/ (double)CLOCKS_PER_SEC > 0.1)
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
	if ((t->spr[i].type == '3' || t->spr[i].type == '5') && !t->spr[i].alive)
		return (21);
	else if (t->spr[i].type == '3' && t->spr[i].mode == 'm')
		return (get_frame_spider_walk(t, i));
	else if (t->spr[i].type == '3' && t->spr[i].mode == 'a')
		return (get_frame_spider_attack(t, i));
	else
		return (23);
}
