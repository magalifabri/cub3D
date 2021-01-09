/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 13:28:24 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/09 19:51:17 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialise_sprite(t_cub3d *t, int y, int x, int i)
{
	t->spr[i].type = t->map[y][x];
	t->spr[i].y = y;
	t->spr[i].x = x;
	t->spr[i].y_draw = 0;
	t->spr[i].x_draw = 0;
	t->spr[i].mod = 0;
	t->spr[i].frame = 0;
	t->spr[i].time_frame_swp = 0;
	t->spr[i].hit = 0;
	if (t->spr[i].type == '3')
	{
		t->spr[i].health = 3;
		t->spr[i].alive = 1;
		t->spr[i].mode = 'i';
	}
	if (t->spr[i].type == '5')
	{
		t->spr[i].health = 3;
		t->spr[i].alive = 1;
		t->spr[i].time_spawn = 0;
	}
}

static void	find_sprites_part_2(t_cub3d *t)
{
	int y;
	int x;
	int i;

	if (!(t->spr = malloc(sizeof(t_sprite) * t->sprite_n)))
		exit_cub3d(t);
	i = 0;
	y = -1;
	while (++y < t->map_h)
	{
		x = -1;
		while (++x < t->map_w)
		{
			if (t->map[y][x] == '2' || t->map[y][x] == '3'
			|| t->map[y][x] == '5')
				initialise_sprite(t, y, x, i++);
		}
	}
}

void		find_sprites(t_cub3d *t)
{
	int y;
	int x;

	t->sprite_n = 0;
	y = -1;
	while (++y < t->map_h)
	{
		x = -1;
		while (++x < t->map_w)
			if (t->map[y][x] == '2' || t->map[y][x] == '3'
			|| t->map[y][x] == '5')
				t->sprite_n++;
	}
	if (t->sprite_n > SPRITE_MAX)
		error_and_exit(t, "Too many sprites on map");
	if (t->sprite_n != 0)
		find_sprites_part_2(t);
}

static void	init_variables(t_cub3d *t, int y, int x)
{
	if (t->map[y][x] == 'N')
	{
		t->p_dir_y = -1;
		t->plane_x = (0.6 / ((double)t->win_h / (double)t->win_w));
	}
	else if (t->map[y][x] == 'E')
	{
		t->p_dir_x = 1;
		t->plane_y = (0.6 / ((double)t->win_h / (double)t->win_w));
	}
	else if (t->map[y][x] == 'S')
	{
		t->p_dir_y = 1;
		t->plane_x = -(0.6 / ((double)t->win_h / (double)t->win_w));
	}
	else
	{
		t->p_dir_x = -1;
		t->plane_y = -(0.6 / ((double)t->win_h / (double)t->win_w));
	}
}

void		find_player(t_cub3d *t)
{
	int y;
	int x;

	y = -1;
	while (++y < t->map_h)
	{
		x = -1;
		while (++x < t->map_w)
		{
			if (t->map[y][x] == 'N' || t->map[y][x] == 'E'
			|| t->map[y][x] == 'S' || t->map[y][x] == 'W')
			{
				if (t->p_x == 0)
				{
					t->p_y = y;
					t->p_x = x;
					init_variables(t, y, x);
				}
				else
					error_and_exit(t, "Multiple player symbols found on map");
			}
		}
	}
	if (t->p_x == 0.0)
		error_and_exit(t, "Player not found on map");
}
