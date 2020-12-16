/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:26:20 by mfabri            #+#    #+#             */
/*   Updated: 2020/04/28 08:51:42 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_resolution(t_cub3d *t, char *file, int *index)
{
	int i;

	i = 0;
	while (file[i] == ' ')
		i++;
	t->win_w = 0;
	while (file[i] >= '0' && file[i] <= '9')
		t->win_w = t->win_w * 10 + (file[i++] - '0');
	while (file[i] == ' ')
		i++;
	t->win_h = 0;
	while (file[i] >= '0' && file[i] <= '9')
		t->win_h = t->win_h * 10 + (file[i++] - '0');
	*index = *index + i;
	if (t->win_w <= 0 || t->win_h <= 0)
	{
		printf("Error\nfailed resolution check\n");
		exit_cub3d(t);
	}
}

static char	*get_texture_path(t_cub3d *t, int n, char *file, int *index)
{
	int		i;
	char	*tex_path;

	i = 0;
	while (*file == ' ')
	{
		file++;
		i++;
	}
	*index = *index + i;
	i = 0;
	while (file[i] > 32 && file[i] < 127)
		i++;
	if (!(tex_path = malloc(i + 1)))
		exit_cub3d(t);
	t->td[n].malloc = 1;
	i = 0;
	while (*file > 32 && *file < 127)
		tex_path[i++] = *file++;
	tex_path[i] = '\0';
	*index = *index + i;
	check_tex_path(t, tex_path, n);
	return (tex_path);
}

static void	get_map_config(t_cub3d *t, char *file)
{
	int i;

	i = -1;
	while (file[++i] && t->map_w == 0)
	{
		if (file[i] == 'R')
			get_resolution(t, file + (i + 1), &i);
		else if (file[i] == 'N' && file[i + 1] == 'O')
			t->td[0].tex_path = get_texture_path(t, 0, file + (i + 2), &i);
		else if (file[i] == 'E' && file[i + 1] == 'A')
			t->td[1].tex_path = get_texture_path(t, 1, file + (i + 2), &i);
		else if (file[i] == 'S' && file[i + 1] == 'O')
			t->td[2].tex_path = get_texture_path(t, 2, file + (i + 2), &i);
		else if (file[i] == 'W' && file[i + 1] == 'E')
			t->td[3].tex_path = get_texture_path(t, 3, file + (i + 2), &i);
		else if (file[i] == 'S')
			t->td[4].tex_path = get_texture_path(t, 4, file + (i + 1), &i);
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
		exit_cub3d(t);
	if (!(file = copy_file(fd)))
		exit_cub3d(t);
	t->map_w = 0;
	t->map_h = 1;
	get_map_config(t, file);
	free(file);
}
