/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:25:12 by mfabri            #+#    #+#             */
/*   Updated: 2020/04/27 16:25:12 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_cub3d(t_cub3d *t)
{
	int i;

	system("killall afplay");
	ft_printf("freeing\n");
	i = t->map_h;
	if (t->malloc_map)
	{
		while (i >= 0)
			free(t->map[i--]);
		free(t->map);
	}
	i = 5;
	while (i--)
		if (t->td[i].malloc == 1)
			free(t->td[i].tex_path);
	free(t->td);
	if (t->malloc_spr)
		free(t->spr);
	system("leaks cub3d > leaks2.txt");
	ft_printf("exiting\n");
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
	(keycode == 46) ? system("killall afplay") : (0);
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

int		exit_hook(int keycode, t_cub3d *t)
{
	exit_cub3d(t);
	return (keycode);
}
