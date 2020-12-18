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

/*
compare_resolutions(): Compares the desired resolution given in the .cub file to 
- 1. the minimum resolutions set in the header (going below these values compromises the functionality program). If the resolutions from the .cub are below these minimum values, they are increased to match them.
- 2. the max resolutions set in the get_screen_resolution() function. If the resolutions given in the .cub file are above these, they are decreased to match them so that the cub3D window fits on the screen.
*/

static void compare_resolutions(t_cub3d *t)
{
	if (t->win_w < MIN_WINDOW_WIDTH)
	{
		printf("Error: Given width resolution too low. Set to minimum\n");
		t->win_w = MIN_WINDOW_WIDTH;
	}
	else if (t->win_w > t->max_win_w)
	{
		printf("Error: Given width resolution too high. Set to max\n");
		t->win_w = t->max_win_w;
	}
	if (t->win_h < MIN_WINDOW_HEIGHT)
	{
		printf("Error: Given height resolution too low. Set to minimum\n");
		t->win_h = MIN_WINDOW_HEIGHT;
	}
	else if (t->win_h > t->max_win_h)
	{
		printf("Error: Given height resolution too high. Set to max.\n");
		t->win_h = t->max_win_h;
	}
}

/*
get_screen_resolution(): Gets the resolution of the screen (and whether it's a retina screen) that the program has been compiled on by interpreting the native_res.txt file (created during compilation). It then sets the max_win_w and max_win_h variables to indicate the maximum window width and height of the cub3D window. The height is decreased a bit because it needs to take the horizontal top macOS menu bar into account.
*/

static void get_screen_resolution(t_cub3d *t)
{
	int fd;
	char *file;
	int i;

	if ((fd = open("native_res.txt", O_RDONLY)) == -1)
		error_and_exit(t, "get_screen_resolution: open() returned NULL");
	file = copy_file(fd);
	close(fd);
	if (!file)
		error_and_exit(t, "get_screen_resolution: copy_file() returned NULL");
	i = 0;
	while (file[i] == ' ')
		i++;
	t->max_win_w = 0;
	while (file[i] >= '0' && file[i] <= '9')
		t->max_win_w = t->max_win_w * 10 + (file[i++] - '0');
	while (file[i] == ' ' || file[i] == 'x')
		i++;
	t->max_win_h = 0;
	while (file[i] >= '0' && file[i] <= '9')
		t->max_win_h = t->max_win_h * 10 + (file[i++] - '0');
	t->retina = (file[i] == ' ') ? 1 : 0;
	(t->retina) && (t->max_win_w /= 2);
	t->max_win_h = t->retina ? (t->max_win_h / 2) - 100 : t->max_win_h - 50;
}

static void	get_window_resolution(t_cub3d *t, char *file, int *index)
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
		error_and_exit(t, "get_window_resolution: resolution in .cub wrong");
	get_screen_resolution(t);
	compare_resolutions(t);
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
		error_and_exit(t, "get_texture_path: malloc error");
	t->td[n].malloc = 1;
	i = 0;
	while (*file > 32 && *file < 127)
		tex_path[i++] = *file++;
	tex_path[i] = '\0';
	*index = *index + i;
	check_tex_path(t, tex_path);
	return (tex_path);
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
		error_and_exit(t, "parse_cub_file: fd < 0");
	file = copy_file(fd);
	close(fd);
	if (!file)
		error_and_exit(t, "parse_cub_file: bad return from copy_file()");
	t->map_w = 0;
	t->map_h = 1;
	get_map_config(t, file);
	free(file);
}
