#include "cub3d.h"

static void	draw_background(t_cub3d *t, int sky, int floor)
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

void		print_terminal_map(t_cub3d *t)
{
	int y;
	int x;

	x = 0;
	y = 0;
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

static void	draw_stuff(t_cub3d *t)
{
	int		i;
	double	z_buf[t->win_w];

	draw_background(t, t->colors[1], t->colors[0]);
	draw_floor(t);
	draw_skybox(t);
	draw_skybox2(t);
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
	if ((double)(t->time_now - t->p_hit) / (double)CLOCKS_PER_SEC < 0.1)
		draw_red_border(t);
}

static int	run_game(t_cub3d *t)
{
	static double	time_last_frame;
	int				s;

	t->time_now = clock();
	play_music(t);
	draw_stuff(t);
	mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
	move(t);
	if (t->shoot == 1)
		shoot(t);
	s = -1;
	while (++s < t->sprite_n)
		sprite_control(t, s);
	t->mouse_move = 0;
	t->shoot = 0;
	if (t->p_health == 0)
		exit(0);
	// print_terminal_map(t);
	t->fps = 1 / ((double)(t->time_now - time_last_frame)
	/ (double)CLOCKS_PER_SEC);
	time_last_frame = t->time_now;
	return (0);
}

// int	check_arguments(int ac, char **av)
// {
// 	int fd;
// 	char *save;
// 	int i;

// 	save = "--save";
// 	i = 0;
// 	if (ac == 3)
// 	{
// 		while (av[2][i] && av[2][i] == save[i])
// 			i++;
// 		if (i == 6)
// 		{
// 			printf("save bmp image\n");
// 			fd = open(av[1], O_RDONLY);
// 		}
// 		else
// 			return (0);
// 	}
// 	else if (ac == 2)
// 	{
// 		fd = open(av[1], O_RDONLY);
// 		printf("%d\n", fd);
// 	}
// 	else
// 		return (0);
// }

int			main(int ac, char **av)
{
	t_cub3d t;
	
	t.td = malloc(sizeof(t_texture_data) * 50);
	initialise_variables(&t);
	parse_cub_file(&t, ac, av);
	t.mlx = mlx_init();
	t.win = mlx_new_window(t.mlx, t.win_w, t.win_h, "cub3D");
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
