/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:44:33 by magali            #+#    #+#             */
/*   Updated: 2021/01/25 19:03:27 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_colour(t_cub3d *t, int r, int g, int b)
{
	int colour;

	if (r < 0 || g < 0 || b < 0
	|| r > 255 || g > 255 || b > 255)
		error_and_exit(t, "problem with ceiling and/or floor colour in .cub");
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

static void	initialise(int *r, int *g, int *b, int *i)
{
	*r = -1;
	*g = -1;
	*b = -1;
	*i = 0;
}

int			get_colour(t_cub3d *t, char *file, int *index, int fc)
{
	int r;
	int g;
	int b;
	int i;

	initialise(&r, &g, &b, &i);
	if (t->colors[fc] != -1)
		error_and_exit(t, "duplicate colour assignment in .cub");
	while (file[i] == ' ')
		i++;
	if (file[i] >= '0' && file[i] <= '9')
		r = get_value(file, &i, ++r);
	while (file[i] == ' ' || file[i] == ',')
		i++;
	if (file[i] >= '0' && file[i] <= '9')
		g = get_value(file, &i, ++g);
	while (file[i] == ' ' || file[i] == ',')
		i++;
	if (file[i] >= '0' && file[i] <= '9')
		b = get_value(file, &i, ++b);
	while (file[i] == ' ')
		i++;
	*index = *index + i;
	return (check_colour(t, r, g, b));
}

int			strings_are_equal(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] == s2[i]);
}
