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
	printf("win_w = %d, win_h = %d\n", t->win_w, t->win_h);
}

static char	*get_texture_path(char *file, int *index)
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
	tex_path = malloc(i + 1);
	i = 0;
	while (*file > 32 && *file < 127)
		tex_path[i++] = *file++;
	tex_path[i] = '\0';
	*index = *index + i;
	printf("path = %s\n", tex_path);
	return (tex_path);
}

static int	get_colour(char *file, int *index)
{
	int r;
	int g;
	int b;
	int i;

	i = 0;
	while (file[i] == ' ')
		i++;
	r = 0;
	while (file[i] >= '0' && file[i] <= '9')
		r = r * 10 + (file[i++] - '0');
	while (file[i] == ' ' || file[i] == ',')
		i++;
	g = 0;
	while (file[i] >= '0' && file[i] <= '9')
		g = g * 10 + (file[i++] - '0');
	while (file[i] == ' ' || file[i] == ',')
		i++;
	b = 0;
	while (file[i] >= '0' && file[i] <= '9')
		b = b * 10 + (file[i++] - '0');
	*index = *index + i;
	printf("color = %d\n", (r * 65536) + (g * 256) + b);
	return ((r * 65536) + (g * 256) + b);
}

static void	get_settings(t_cub3d *t, char *file)
{
	int i;

	i = -1;
	while (file[++i] && t->map_w == 0)
	{
		if (file[i] == 'R')
			get_resolution(t, file + (i + 1), &i);
		else if (file[i] == 'N' && file[i + 1] == 'O')
			t->td[0].tex_path = get_texture_path(file + (i + 2), &i);
		else if (file[i] == 'E' && file[i + 1] == 'A')
			t->td[1].tex_path = get_texture_path(file + (i + 2), &i);
		else if (file[i] == 'S' && file[i + 1] == 'O')
			t->td[2].tex_path = get_texture_path(file + (i + 2), &i);
		else if (file[i] == 'W' && file[i + 1] == 'E')
			t->td[3].tex_path = get_texture_path(file + (i + 2), &i);
		else if (file[i] == 'S')
			t->td[4].tex_path = get_texture_path(file + (i + 1), &i);
		else if (file[i] == 'F')
			t->colors[0] = get_colour(file + (i + 1), &i);
		else if (file[i] == 'C')
			t->colors[1] = get_colour(file + (i + 1), &i);
		else if (file[i] == ' ' || file[i] == '1')
			parse_map(t, file + i);
	}
}

int	check_arguments(int ac, char **av)
{
	int fd;
	char *save;
	int i;

	save = "--save";
	i = 0;
	if (ac == 2)
		return (open(av[1], O_RDONLY));
	if (ac == 3 && (fd = open(av[1], O_RDONLY)) >= 0)
	{
		while (av[2][i] && av[2][i] == save[i])
			i++;
		if (i == 6)
		{
			printf("save bmp image\n");
			return (0);
		}
	} 
	return (-1);
}

int		parse_cub_file(t_cub3d *t, int ac, char **av)
{
	char	*file;
	int		fd;

	fd = check_arguments(ac, av);
	// fd = open("./maps/cubfile_dark.cub", O_RDONLY);
	file = copy_file(fd);
	t->map_w = 0;
	t->map_h = 1;
	get_settings(t, file);
	return (1);
}
