/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:02:40 by mfabri            #+#    #+#             */
/*   Updated: 2020/04/27 18:46:51 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (t->p_health == 0)
	{
		printf("YOU ARE SPIDER FOOD\n");
		exit_cub3d(t);
	}
	t->fps = 1 / ((double)(t->time_now - time_last_frame)
	/ (double)CLOCKS_PER_SEC);
	time_last_frame = t->time_now;
	if (t->save == 1)
		get_bmp(t);
	return (0);
}

static void	initialise_variables_2(t_cub3d *t)
{
	t->td[0].malloc = 0;
	t->td[1].malloc = 0;
	t->td[2].malloc = 0;
	t->td[3].malloc = 0;
	t->td[4].malloc = 0;
}

static void	initialise_variables(t_cub3d *t)
{
	t->save = 0;
	t->error = 0;
	t->spd = 3;
	t->w = 0;
	t->s = 0;
	t->a = 0;
	t->d = 0;
	t->l_a = 0;
	t->r_a = 0;
	t->mouse_move = 0;
	t->map_w = 0;
	t->p_dir_x = 0;
	t->p_dir_y = 0;
	t->plane_x = 0;
	t->plane_y = 0;
	t->shoot = 0;
	t->p_health = 5;
	t->p_bullets = 5;
	t->p_hit = 0;
	t->malloc_map = 0;
	t->malloc_tex_paths = 0;
	t->malloc_spr = 0;
	t->malloc_td = 1;
	initialise_variables_2(t);
}

int			main(int ac, char **av)
{
	t_cub3d t;

	if (!(t.td = malloc(sizeof(t_texture_data) * 50)))
		return (0);
	initialise_variables(&t);
	parse_cub_file(&t, ac, av);
	t.mlx = mlx_init();
	t.win = mlx_new_window(t.mlx, t.win_w, t.win_h, "cub3D");
	t.img = mlx_new_image(t.mlx, t.win_w, t.win_h);
	t.addr = mlx_get_data_addr(t.img, &t.bpp, &t.line_len, &t.endian);
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
