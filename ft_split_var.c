#include "cub3d.h"

static int ft_get_length(char *map)
{
    int max;

    max = 1;
    while (*map)
        if (*map++ == '\n')
            max++;
    return (max);
}

static char		*ft_get_row(char *s, int width)
{
	int		i;
	char	*row;

	i = 0;
	if (width == 0)
		while (s[i] && s[i] != '\n')
			i++;
	if (!(row = malloc(sizeof(char) * width + i + 1)))
		return (NULL);
	if (width != 0)
		while (i <= width)
			row[i++] = '0';
	i = 0;
	while (*s && *s != '\n')
	{
		if (*s == ' ')
			row[i++] = (width != 0) ? ('0') : (' ');
			// if (width != 0)
			// 	row[i++] = '0';
			// else
			// 	row[i++] = ' ';
		else
			row[i++] = *s;
		s++;
	}
	row[i] = '\0';
	return (row);
}

char		**ft_split_var(char *s, t_cub3d *t)
{
	int		i;
	char	**array;

	if (!s)
		return (NULL);
	if (!(array = malloc(sizeof(char*) * (ft_get_length(s) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == '\n')
			s++;
		if (*s && *s != '\n')
		{
			array[i] = ft_get_row(s, t->map_w);
			i++;
			while (*s && *s != '\n')
				s++;
		}
	}
	array[i] = NULL;
	return (array);
}
