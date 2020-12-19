/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:44:33 by magali            #+#    #+#             */
/*   Updated: 2020/12/19 19:47:18 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_tex_path(t_cub3d *t, char *tex_path)
{
	int fd;

	if ((fd = open(tex_path, O_RDONLY)) < 0)
	{
		ft_printf(B_RED"Error: Bad texture path: %s"RESET"\n", tex_path);
		exit_cub3d(t);
	}
	close(fd);
}

int			check_colour(t_cub3d *t, int r, int g, int b)
{
	int colour;

	if (r < 0 || g < 0 || b < 0
	|| r > 255 || g > 255 || b > 255)
		error_and_exit(t, "check_colour: Failed colour check");
	colour = (r * 65536) + (g * 256) + b;
	return (colour);
}

static int	get_value(char *file, int *i, int value)
{
	while (file[*i] >= '0' && file[*i] <= '9')
	{
		value = value * 10 + (file[*i] - '0');
		*i = *i + 1;
	}
	return (value);
}

int			get_colour(t_cub3d *t, char *file, int *index)
{
	int r;
	int g;
	int b;
	int i;

	i = 0;
	while (file[i] == ' ')
		i++;
	r = -1;
	if (file[i] >= '0' && file[i] <= '9')
		r = get_value(file, &i, ++r);
	while (file[i] == ' ' || file[i] == ',')
		i++;
	g = -1;
	if (file[i] >= '0' && file[i] <= '9')
		g = get_value(file, &i, ++g);
	while (file[i] == ' ' || file[i] == ',')
		i++;
	b = -1;
	if (file[i] >= '0' && file[i] <= '9')
		b = get_value(file, &i, ++b);
	*index = *index + i;
	return (check_colour(t, r, g, b));
}

int			check_arguments(t_cub3d *t, int ac, char **av)
{
	int		fd;
	char	*save;
	int		i;

	fd = open(av[1], O_RDONLY);
	save = "--save";
	if (ac == 2)
		return (fd);
	if (ac == 3 && fd >= 0)
	{
		i = 0;
		while (av[2][i] && av[2][i] == save[i])
			i++;
		if (i == 6)
		{
			ft_printf("saving bmp image...\n");
			t->save = 1;
			return (fd);
		}
	}
	return (-1);
}
