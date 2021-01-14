/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:25:12 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/14 18:41:09 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** To test for leaks, put the following line just above "exit(0);":
** system("leaks cub3d > leaks2.txt");
*/

int		exit_cub3d(t_cub3d *t)
{
	int i;

	ft_printf("exiting\n");
	if (t->music_playing)
		system("killall afplay");
	i = t->map_h;
	if (t->map != NULL)
	{
		while (i >= 0)
			free(t->map[i--]);
		free(t->map);
	}
	i = 5;
	while (i--)
		if (t->td[i].tex_path != NULL)
			free(t->td[i].tex_path);
	free(t->td);
	if (t->spr != NULL)
		free(t->spr);
	exit(0);
}

int		keypress_hook(int keycode, t_cub3d *t)
{
	static double previous_time;

	if (keycode == 53)
		exit_cub3d(t);
	else if (keycode == 123)
		t->l_a = 1;
	else if (keycode == 124)
		t->r_a = 1;
	else if (keycode == 13)
		t->w = 1;
	else if (keycode == 1)
		t->s = 1;
	else if (keycode == 0)
		t->a = 1;
	else if (keycode == 2)
		t->d = 1;
	else if (t->p_bullets > 0 && keycode == 49
	&& (double)(t->time_now - previous_time) / (double)CLOCKS_PER_SEC > 0.5)
	{
		t->shoot = 1;
		previous_time = t->time_now;
		t->p_bullets--;
	}
	(keycode == 46 && t->music_playing) ? stop_music(t) : (0);
	return (0);
}

int		keyrelease_hook(int keycode, t_cub3d *t)
{
	if (keycode == 123)
		t->l_a = 0;
	else if (keycode == 124)
		t->r_a = 0;
	else if (keycode == 13)
		t->w = 0;
	else if (keycode == 1)
		t->s = 0;
	else if (keycode == 0)
		t->a = 0;
	else if (keycode == 2)
		t->d = 0;
	return (0);
}

int		mouse_move_hook(int current_mouse_x, int current_mouse_y, t_cub3d *t)
{
	if (current_mouse_x == t->prev_mouse_x)
		return (0);
	if (current_mouse_x >= t->win_w && t->prev_mouse_x < t->win_w - 100)
		current_mouse_x = (t->win_w / 2);
	else if (current_mouse_x <= 0 && t->prev_mouse_x > 100)
		current_mouse_x = (t->win_w / 2);
	t->mouse_move = current_mouse_x - t->prev_mouse_x;
	t->prev_mouse_x = current_mouse_x;
	if (current_mouse_x <= 0)
	{
		mlx_mouse_move(t->win, t->win_w / 2, t->win_h / 2);
		t->prev_mouse_x = current_mouse_x + t->win_w / 2;
	}
	else if (current_mouse_x >= t->win_w)
	{
		mlx_mouse_move(t->win, t->win_w / 2, t->win_h / 2);
		t->prev_mouse_x = current_mouse_x - t->win_w / 2;
	}
	if (current_mouse_y <= 0 || current_mouse_y >= t->win_h)
		mlx_mouse_move(t->win, current_mouse_x, t->win_h / 2);
	return (current_mouse_y);
}
