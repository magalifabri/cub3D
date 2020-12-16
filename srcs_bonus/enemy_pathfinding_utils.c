/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_pathfinding_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:18:52 by mfabri            #+#    #+#             */
/*   Updated: 2020/04/27 16:18:53 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			obstacle(char c)
{
	return (c == '1' || c == '2' || c == '5');
}

static void	move_enemy_part_2(t_cub3d *t, int i)
{
	if (t->map[(int)t->spr[i].y][(int)t->spr[i].x] != '5')
		t->map[(int)t->spr[i].y][(int)t->spr[i].x] = '0';
	t->spr[i].y = t->spr[i].y + (t->spr[i].y_draw * 10);
	t->spr[i].x = t->spr[i].x + (t->spr[i].x_draw * 10);
	t->map[(int)t->spr[i].y][(int)t->spr[i].x] = '3';
	t->spr[i].mod = 0;
}

void		move_enemy(t_cub3d *t, int i)
{
	static double time_move[10];

	if (t->path_steps < 2)
		return ;
	if ((double)(t->time_now - time_move[i]) / (double)CLOCKS_PER_SEC > 0.05)
	{
		if (t->spr[i].mod == 0)
		{
			t->spr[i].y_draw = 0;
			t->spr[i].x_draw = 0;
			if (t->l[t->path_steps].direction_of_origin == 'n')
				t->spr[i].y_draw = -0.1;
			else if (t->l[t->path_steps].direction_of_origin == 's')
				t->spr[i].y_draw = 0.1;
			else if (t->l[t->path_steps].direction_of_origin == 'e')
				t->spr[i].x_draw = 0.1;
			else if (t->l[t->path_steps].direction_of_origin == 'w')
				t->spr[i].x_draw = -0.1;
		}
		t->spr[i].mod++;
		if (t->spr[i].mod == 10)
			move_enemy_part_2(t, i);
		time_move[i] = t->time_now;
	}
}
