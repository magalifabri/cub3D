/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:27:11 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/20 12:08:07 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_charset(char i)
{
	return (i == '0' || i == '1' || i == '2' || i == '3' || i == '5'
	|| i == 'N' || i == 'S' || i == 'E' || i == 'W' || i == ' ' || i == '\n');
}

static void	get_map_dimensions(char *map, t_cub3d *t)
{
	int i;

	i = 0;
	while (*map && check_charset(*map))
	{
		if (*map == '\n')
		{
			t->map_w = (i > t->map_w) ? (i) : (t->map_w);
			i = 0;
			map++;
			t->map_h++;
		}
		i++;
		(*map) && (map++);
	}
	(i == 1) && (t->map_h--);
	if (*map != '\0')
		error_and_exit(t, "Encountered unknown character in map");
}

static void	find_player_part_2(t_cub3d *t, int y, int x)
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

static void	find_player(t_cub3d *t)
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
				t->p_y = y;
				t->p_x = x;
				find_player_part_2(t, y, x);
				return ;
			}
		}
	}
	error_and_exit(t, "Player not found on map");
}

void		parse_map(t_cub3d *t, char *file)
{
	get_map_dimensions(file, t);
	if (!(t->map = ft_split_var(file, t)))
		error_and_exit(t, "parse_map: ft_split_var returned NULL");
	t->malloc_map = 1;
	check_map_horizontally(t);
	check_map_vertically(t);
	find_player(t);
	find_sprites(t);
}
