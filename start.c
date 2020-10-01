#include "cub3d.h"

void ft_putpxl(t_cub3d *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr[0] + (y * data->line_len[0] + x * (data->bpp[0] / 8));
	*(unsigned int *)dst = color;
}

void draw_background(t_cub3d *t, int sky, int floor)
{
	int x;
	int y;
	y = 0;
	while (y < (t->win_h / 2))
	{
		x = 0;
		while (x < t->win_w)
			ft_putpxl(t, x++, y, sky);
		y++;
	}
	while (y < t->win_h)
	{
		x = 0;
		while (x < t->win_w)
			ft_putpxl(t, x++, y, floor);
		y++;
	}
}

double spawn_mobs(t_cub3d *t, int nest)
{
	int sprite;

	sprite = -1;
	while (++sprite < t->sprite_n)
	{
		if (t->spr[sprite].type == '0')
		{
			t->spr[sprite].x = t->spr[nest].x + 1;
			t->spr[sprite].y = t->spr[nest].y;
			t->spr[sprite].type = '3';
			t->spr[sprite].health = 3;
			t->spr[sprite].hit = 0;
			t->spr[sprite].alive = 1;
			t->spr[sprite].mode = 'i';
			t->spr[nest].time_spawn = t->time_now;
			break ;
		}
	}
	return (clock());
}

void draw_stuff(t_cub3d *t)
{
	int sprite;
	int i;
	double z_buf[t->win_w];

	draw_background(t, t->colors[1], t->colors[0]);
	draw_floor(t);
	draw_skybox(t);
	draw_skybox2(t);
	if (t->shoot == 1)
		cast_ray(t);
	i = -1;
	while (++i < t->win_w)
		z_buf[i] = draw_walls(t, i);
	if (t->sprite_n != 0)
		draw_sprites(t, z_buf);
	draw_crosshair(t);
	draw_torch(t);
	draw_gun(t);
	draw_hearts(t);
	draw_bullets(t);
	sprite = -1;
	if ((double)(t->time_now - t->p_hit) / (double)CLOCKS_PER_SEC < 0.1)
		draw_red_border(t);
}

int run_game(t_cub3d *t)
{
	static double last_mob_spawn;
	static double time_last_frame;
	int sprite;

	t->time_now = clock();
	// play_music();
	draw_stuff(t);
	mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
	sprite = -1;
	while (++sprite < t->sprite_n)
		if (t->spr[sprite].type == '5' && t->spr[sprite].alive
		&& (t->spr[sprite].time_spawn == 0 
		|| (double)(t->time_now - t->spr[sprite].time_spawn) / (double)CLOCKS_PER_SEC > 5))
			last_mob_spawn = spawn_mobs(t, sprite);
	move(t);
	find_path(t);
	t->mouse_move = 0;
	if (t->p_health == 0)
		exit(0);

	// int y = 0;
	// int x = 0;
	// while (y < t->map_h)
	// {
	// 	 while (x <= t->map_w)
	// 	 {
	// 		 printf("%c", t->map[y][x]);
	// 		 x++;
	// 	 }
	// 	 printf("\n");
	// 	 x = 0;
	// 	 y++;
	// }

	t->fps = 1 / ((double)(t->time_now - time_last_frame) / (double)CLOCKS_PER_SEC);
	time_last_frame = t->time_now;
	return (0);
}

int main(void)
{
	t_cub3d t;

	ft_init(&t);
	parse_cub_file(&t);
	t.mlx = mlx_init();
	t.win = mlx_new_window(t.mlx, t.win_w, t.win_h, "Hello world!");
	t.img = mlx_new_image(t.mlx, t.win_w, t.win_h);
	t.addr[0] = mlx_get_data_addr(t.img, &t.bpp[0], &t.line_len[0], &t.endian[0]);
	mlx_mouse_hide();
	mlx_mouse_move(t.win, t.win_w / 2, t.win_h / 2);
	t.prev_mouse_x = t.win_w / 2;
	get_textures(&t);
	mlx_hook(t.win, 2, 1L << 0, keypress_hook, &t);
	mlx_hook(t.win, 3, 1L << 1, keyrelease_hook, &t);
	mlx_hook(t.win, 6, 1L << 6, mouse_move_hook, &t);
	mlx_hook(t.win, 17, 0, exit_hook, &t);
	mlx_loop_hook(t.mlx, run_game, &t);
	mlx_loop(t.mlx);
	return (0);
}
