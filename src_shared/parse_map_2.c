/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 13:28:24 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/22 13:51:20 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_map_horizontally(t_cub3d *t)
{
	int y;
	int x;

	y = -1;
	while (++y < t->map_h)
	{
		x = -1;
		while (++x < t->map_w)
		{
			if ((t->map[y][x] != '1' && t->map[y][x] != ','
			&& (t->map[y][x + 1] == '\0' || t->map[y][x + 1] == ','))
			|| ((t->map[y][x] == ',' && t->map[y][x + 1] != '1'
			&& t->map[y][x + 1] != ',' && t->map[y][x + 1] != '\0'))
			|| ((x == 0 && t->map[y][x] != ',' && t->map[y][x] != '1')))
				error_and_exit(t, "Found a hole in a wall");
		}
	}
}

void		check_map_vertically(t_cub3d *t)
{
	int y;
	int x;

	x = -1;
	while (++x < t->map_w)
	{
		y = -1;
		while (++y < t->map_h)
		{
			if ((t->map[y][x] != '1' && t->map[y][x] != ','
			&& (t->map[y + 1][x] == '\0' || t->map[y + 1][x] == ','))
			|| ((t->map[y][x] == ',' && t->map[y + 1][x] != '1'
			&& t->map[y + 1][x] != ',' && t->map[y + 1][x] != '\0'))
			|| ((y == 0 && t->map[y][x] != ',' && t->map[y][x] != '1')))
				error_and_exit(t, "Found a hole in a wall");
		}
	}
}

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
	if (t->sprite_n != 0)
		find_sprites_part_2(t);
}
