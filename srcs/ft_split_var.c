/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:21:09 by mfabri            #+#    #+#             */
/*   Updated: 2020/04/27 16:21:55 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_get_length(char *map)
{
	int max;

	max = 1;
	while (*map)
		if (*map++ == '\n')
			max++;
	return (max);
}

static char	*ft_get_row(char *s, int width)
{
	int		i;
	char	*row;

	if (!(row = malloc(sizeof(char) * width + 1)))
		return (NULL);
	i = 0;
	while (i <= width)
		row[i++] = ',';
	i = 0;
	while (*s && *s != '\n')
	{
		row[i++] = (*s == ' ') ? ',' : *s;
		s++;
	}
	row[width] = '\0';
	return (row);
}

static void	*malloc_error_abort(char **array, int i)
{
	while (i >= 0)
	{
		free(array[i]);
		array[i--] = NULL;
	}
	free(array);
	return (NULL);
}

char		**ft_split_var(char *s, t_cub3d *t)
{
	int		i;
	char	**array;

	if (!s)
		return (NULL);
	if (!(array = malloc(sizeof(char*) * (ft_get_length(s) + 2))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == '\n')
			s++;
		if (*s && *s != '\n')
		{
			if (!(array[i] = ft_get_row(s, t->map_w)))
				return (malloc_error_abort(array, i));
			i++;
			while (*s && *s != '\n')
				s++;
		}
	}
	if (!(array[i++] = ft_get_row(s, t->map_w)))
		return (malloc_error_abort(array, i));
	array[i] = NULL;
	return (array);
}
