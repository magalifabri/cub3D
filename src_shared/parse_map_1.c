/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:27:11 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/23 14:50:17 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_vertically(t_cub3d *t)
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
				error_and_exit(t, "found a hole in a wall");
		}
	}
}

static void	check_map_horizontally(t_cub3d *t)
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
				error_and_exit(t, "found a hole in a wall");
		}
	}
}

static void check_for_more(char *map, t_cub3d *t)
{
	while (*map)
		if (*map++ != '\n')
			error_and_exit(t, "characters encountered after map");
}

static void get_map_dimensions(char *map, t_cub3d *t)
{
	int i;

	i = 0;
	while (*map && char_is_valid(*map))
	{
		if (*map == '\n')
		{
			if (map[1] == '\n')
				break ;
			t->map_w = (i > t->map_w) ? (i) : (t->map_w);
			i = 0;
			map++;
			t->map_h++;
		}
		i++;
		(*map && char_is_valid(*map)) && (map++);
	}
	t->map_w = (i > t->map_w) ? (i) : (t->map_w);
	(i == 1) && (t->map_h--);
	if (*map != '\0' && *map != '\n')
		error_and_exit(t, "encountered invalid character in (or after) map");
	check_for_more(map, t);
}

void		parse_map(t_cub3d *t, char *file)
{
	if (!t->win_w || !t->win_h || t->colors[0] == -1 || t->colors[1] == -1
	|| !t->td[0].tex_path || !t->td[1].tex_path || !t->td[2].tex_path
	|| !t->td[3].tex_path || !t->td[4].tex_path)
		error_and_exit(t, "map not at end or parameters missing in .cub");
	get_map_dimensions(file, t);
	if (t->map_w == 0)
		error_and_exit(t, "no map in .cub");
	if (!(t->map = ft_split_var(file, t)))
		error_and_exit(t, "parse_map: ft_split_var returned NULL");
	check_map_horizontally(t);
	check_map_vertically(t);
	find_player(t);
	find_sprites(t);
}
