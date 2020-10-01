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
		if (*map++ == '\n')
		{
			t->map_w = (i > t->map_w) ? (i) : (t->map_w);
			i = 0;
			map++;
			t->map_h++;
		}
		i++;
	}
}

static void	find_player_part_2(t_cub3d *t, int y, int x)
{
	if (t->map[y][x] == 'N')
	{
		t->p_dir_y = -1;
		t->plane_x = 0.66;
	}
	else if (t->map[y][x] == 'E')
	{
		t->p_dir_x = 1;
		t->plane_y = 0.66;
	}
	else if (t->map[y][x] == 'S')
	{
		t->p_dir_y = 1;
		t->plane_x = -0.66;
	}
	else
	{
		t->p_dir_x = -1;
		t->plane_y = -0.66;
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
}

void		parse_map(t_cub3d *t, char *file)
{
	get_map_dimensions(file, t);
	printf("width = %d, length = %d\n", t->map_w, t->map_h);
	t->map = ft_split_var(file, t);
	find_player(t);
	find_sprites(t);
	
	// print map, remove or use ft_printf
	int y = 0;
	int x = 0;
	while (y < t->map_h)
	{
		while (x <= t->map_w)
		{
			printf("%c", t->map[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}
