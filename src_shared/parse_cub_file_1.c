/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:26:20 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/23 15:59:01 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_texture_path(t_cub3d *t, int n, char *file, int *index)
{
	int		i;

	i = 0;
	while (*file == ' ')
	{
		file++;
		i++;
	}
	*index += i;
	i = 0;
	while (file[i] > 32 && file[i] < 127)
		i++;
	if (!(t->td[n].tex_path = malloc(i + 1)))
		error_and_exit(t, "get_texture_path: malloc error");
	i = 0;
	while (*file > 32 && *file < 127)
		t->td[n].tex_path[i++] = *file++;
	t->td[n].tex_path[i] = '\0';
	check_tex_path(t, t->td[n].tex_path);
	while (*file == ' ')
	{
		file++;
		i++;
	}
	*index += i + 1;
}

static void	get_map_config(t_cub3d *t, char *file)
{
	int i;

	i = -1;
	while (file[++i] && t->map_w == 0)
	{
		if (file[i] == 'R')
			get_window_resolution(t, file + (i + 1), &i);
		else if (file[i] == 'N' && file[i + 1] == 'O')
			get_texture_path(t, 0, file + (i + 2), &i);
		else if (file[i] == 'E' && file[i + 1] == 'A')
			get_texture_path(t, 1, file + (i + 2), &i);
		else if (file[i] == 'S' && file[i + 1] == 'O')
			get_texture_path(t, 2, file + (i + 2), &i);
		else if (file[i] == 'W' && file[i + 1] == 'E')
			get_texture_path(t, 3, file + (i + 2), &i);
		else if (file[i] == 'S')
			get_texture_path(t, 4, file + (i + 1), &i);
		else if (file[i] == 'F')
			t->colors[0] = get_colour(t, file + (i + 1), &i);
		else if (file[i] == 'C')
			t->colors[1] = get_colour(t, file + (i + 1), &i);
		else if (file[i] == ' ' || file[i] == '1')
			parse_map(t, file + i);
	}
}

void		parse_cub_file(t_cub3d *t, int ac, char **av)
{
	char	*file;
	int		fd;

	fd = check_arguments(t, ac, av);
	if (fd < 0)
		error_and_exit(t, "parse_cub_file: fd < 0");
	file = copy_file(fd);
	close(fd);
	if (!file)
		error_and_exit(t, "parse_cub_file: bad return from copy_file()");
	t->map_w = 0;
	t->map_h = 1;
	get_map_config(t, file);
	if (!t->win_w || !t->win_h || t->colors[0] == -1 || t->colors[1] == -1
	|| !t->td[0].tex_path || !t->td[1].tex_path || !t->td[2].tex_path
	|| !t->td[3].tex_path || !t->td[4].tex_path || !t->map_w)
		error_and_exit(t, "missing parameters in .cub");
	free(file);
}
