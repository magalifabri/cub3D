/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:02:40 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/22 13:52:58 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Difference from bonus:
** - no floor
** - no skyboxes
** - no UI elements (crosshair, torch, gun, life bar, bullets, red border)
** - no music
** - no combat (shooting, animated sprites)
** - no mouse capturing and control
*/

static void	draw_stuff(t_cub3d *t)
{
	int		i;
	double	z_buf[t->win_w];

	draw_background(t, t->colors[1], t->colors[0]);
	i = -1;
	while (++i < t->win_w)
		z_buf[i] = draw_walls(t, i);
	if (t->sprite_n != 0)
		draw_sprites(t, z_buf);
}

static int	run_game(t_cub3d *t)
{
	static double	time_last_frame;

	t->time_now = clock();
	draw_stuff(t);
	mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
	move(t);
	t->fps = 1 / ((double)(t->time_now - time_last_frame)
	/ (double)CLOCKS_PER_SEC);
	time_last_frame = t->time_now;
	if (t->save == 1)
		get_bmp(t);
	return (0);
}

static void	initialise_variables_2(t_cub3d *t)
{
	t->map = NULL;
	t->spr = NULL;
	t->td[0].tex_path = NULL;
	t->td[1].tex_path = NULL;
	t->td[2].tex_path = NULL;
	t->td[3].tex_path = NULL;
	t->td[4].tex_path = NULL;
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
	t->p_x = 0;
	t->p_y = 0;
	t->p_dir_x = 0;
	t->p_dir_y = 0;
	t->plane_x = 0;
	t->plane_y = 0;
	t->shoot = 0;
	t->p_health = 5;
	t->p_bullets = 5;
	t->p_hit = 0;
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
	get_textures(&t);
	mlx_hook(t.win, 2, 1L << 0, keypress_hook, &t);
	mlx_hook(t.win, 3, 1L << 1, keyrelease_hook, &t);
	mlx_hook(t.win, 17, 0, exit_hook, &t);
	mlx_loop_hook(t.mlx, run_game, &t);
	mlx_loop(t.mlx);
	return (0);
}
