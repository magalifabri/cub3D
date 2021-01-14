/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:25:12 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/14 18:41:17 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Differences from bonus:
**	- no turning off music in exit_cub3d()
**	- no keyhook for turning off music in keypress_hook()
**	- no keyhook for shooting in keypress_hook()
**	- no mouse_move_hook()
*/

/*
** To test for leaks, put the following line just above "exit(0);":
** system("leaks cub3d > leaks2.txt");
*/

int		exit_cub3d(t_cub3d *t)
{
	int i;

	ft_printf("exiting\n");
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
