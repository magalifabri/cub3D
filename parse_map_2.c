#include "cub3d.h"

static void	initialise_sprite(t_cub3d *t, int y, int x, int i)
{
	t->spr[i].type = t->map[y][x];
	t->spr[i].y = y;
	t->spr[i].x = x;
	t->spr[i].y_draw = 0;
	t->spr[i].x_draw = 0;
	t->spr[i].mod = 0;
	t->spr[i].frame = 0;
	t->spr[i].time_frame_swp = 0;
	t->spr[i].hit = 0;
	if (t->spr[i].type == '3')
	{
		t->spr[i].health = 3;
		t->spr[i].alive = 1;
		t->spr[i].mode = 'i';
	}
	if (t->spr[i].type == '5')
	{
		t->spr[i].health = 3;
		t->spr[i].alive = 1;
	}
}

static void	find_sprites_part_2(t_cub3d *t)
{
	int y;
	int x;
	int i;

	t->spr = malloc(sizeof(t_sprite) * t->sprite_n);
	i = 0;
	y = -1;
	while (++y < t->map_h)
	{
		x = -1;
		while (++x < t->map_w)
		{
			if (t->map[y][x] == '2' || t->map[y][x] == '3'
			|| t->map[y][x] == '5')
			{
				initialise_sprite(t, y, x, i);
				printf("location of sprite %d of type %c: %f, %f\n", i, t->spr[i].type, t->spr[i].y, t->spr[i].x);
				i++;
			}
		}
	}
}

void		find_sprites(t_cub3d *t)
{
	int y;
	int x;

	t->sprite_n = 0;
	y = -1;
	while (++y < t->map_h)
	{
		x = -1;
		while (++x < t->map_w)
			if (t->map[y][x] == '2' || t->map[y][x] == '3'
			|| t->map[y][x] == '5')
				t->sprite_n++;
	}
	printf("number of sprites = %d\n", t->sprite_n);
	if (t->sprite_n != 0)
		find_sprites_part_2(t);
}
