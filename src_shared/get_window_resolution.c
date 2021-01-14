/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window_resolution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:51:18 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/14 20:41:15 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** compare_resolutions(): Compares the desired resolution given in the .cub
** file to:
** - 1. the minimum resolutions set in the header (going below these values
**      compromises the functionality of the program). If the resolutions from
**      the .cub are below these minimum values, they are increased to match
**      them.
** - 2. the max resolutions set in the get_screen_resolution() function. If the
**      resolutions given in the .cub file are above these, they are decreased
**      to match them so that the cub3D window fits on the screen.
*/

static void	compare_resolutions(t_cub3d *t)
{
	if (t->win_w < MIN_WINDOW_WIDTH)
	{
		ft_printf("Error\nGiven width resolution too low. Set to minimum\n");
		t->win_w = MIN_WINDOW_WIDTH;
	}
	else if (t->win_w > t->max_win_w)
	{
		ft_printf("Error\nGiven width resolution too high. Set to max\n");
		t->win_w = t->max_win_w;
	}
	if (t->win_h < MIN_WINDOW_HEIGHT)
	{
		ft_printf("Error\nGiven height resolution too low. Set to minimum\n");
		t->win_h = MIN_WINDOW_HEIGHT;
	}
	else if (t->win_h > t->max_win_h)
	{
		ft_printf("Error\nGiven height resolution too high. Set to max.\n");
		t->win_h = t->max_win_h;
	}
}

static char	*ft_strstr(const char *haystack, const char *needle)
{
	unsigned int i;
	unsigned int j;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && (haystack[i + j] == needle[j]))
			j++;
		if (!needle[j])
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

/*
** get_screen_resolution(): Gets the resolution of the screen (and whether it's
** a retina screen) that the program has been compiled on by interpreting the
** native_res.txt file (created during compilation). It then sets the max_win_w
** and max_win_h variables to indicate the maximum window width and height of
** the cub3D window. The height is decreased a bit because it needs to take the
** horizontal top macOS menu bar into account.
*/

static void	get_screen_resolution(t_cub3d *t)
{
	int		fd;
	char	*file;
	int		i;

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
	t->retina = (ft_strstr(file, "retina")) ? 1 : 0;
	free(file);
	(t->retina) && (t->max_win_w /= 2);
	t->max_win_h = t->retina ? (t->max_win_h / 2) - 100 : t->max_win_h - 50;
}

void		get_window_resolution(t_cub3d *t, char *file, int *index)
{
	int i;

	i = 0;
	while (file[i] == ' ')
		i++;
	while (file[i] >= '0' && file[i] <= '9')
		t->win_w = t->win_w * 10 + (file[i++] - '0');
	while (file[i] == ' ')
		i++;
	while (file[i] >= '0' && file[i] <= '9')
		t->win_h = t->win_h * 10 + (file[i++] - '0');
	if (t->win_w <= 0 || t->win_h <= 0)
		error_and_exit(t, "get_window_resolution: resolution in .cub wrong");
	get_screen_resolution(t);
	compare_resolutions(t);
	while (file[i] == ' ')
		i++;
	*index += i + 1;
}
