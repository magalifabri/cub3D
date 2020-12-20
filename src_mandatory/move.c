/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:25:51 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/20 11:44:09 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Difference from bonus:
** - no wall or sprite collision
** - no map manipulation (needed for pathing(?))
*/

static void	move_forward(t_cub3d *t, double move_spd)
{
	double	new_y;
	double	new_x;

	if (t->s == 0)
	{
		new_y = t->p_dir_y * move_spd;
		t->p_y += new_y;
		new_x = t->p_dir_x * move_spd;
		t->p_x += new_x;
	}
}

static void	move_backward(t_cub3d *t, double move_spd)
{
	double	new_y;
	double	new_x;

	if (t->w == 0)
	{
		new_y = t->p_dir_y * move_spd;
		t->p_y -= new_y;
		new_x = t->p_dir_x * move_spd;
		t->p_x -= new_x;
	}
}

static void	strafe_left(t_cub3d *t, double move_spd)
{
	double	new_y;
	double	new_x;

	if (t->d == 0)
	{
		new_y = t->p_y + (t->p_dir_y * cos(90 * RD)
		- t->p_dir_x * sin(90 * RD)) * move_spd;
		t->p_y = new_y;
		new_x = t->p_x + (t->p_dir_y * sin(90 * RD)
		+ t->p_dir_x * cos(90 * RD)) * move_spd;
		t->p_x = new_x;
	}
}

static void	strafe_right(t_cub3d *t, double move_spd)
{
	double	new_y;
	double	new_x;

	if (t->a == 0)
	{
		new_y = t->p_y - (t->p_dir_y * cos(90 * RD)
		- t->p_dir_x * sin(90 * RD)) * move_spd;
		t->p_y = new_y;
		new_x = t->p_x - (t->p_dir_y * sin(90 * RD)
		+ t->p_dir_x * cos(90 * RD)) * move_spd;
		t->p_x = new_x;
	}
}

void		move(t_cub3d *t)
{
	double	move_spd;
	double	rot_spd;
	double	mouse_spd;

	if (isinf(t->fps))
		t->fps = 10;
	move_spd = (t->fps / (t->fps * t->fps)) * 3;
	rot_spd = (t->fps / (t->fps * t->fps)) * 2;
	mouse_spd = t->mouse_move * 0.05;
	if ((t->w && t->a) || (t->w && t->d)
	|| (t->s && t->a) || (t->s && t->d))
		move_spd *= 0.75;
	if (t->w)
		move_forward(t, move_spd);
	if (t->s)
		move_backward(t, move_spd);
	if (t->l_a || t->mouse_move < 0)
		turn_left(t, rot_spd);
	if (t->r_a || t->mouse_move > 0)
		turn_right(t, rot_spd);
	if (t->a)
		strafe_left(t, move_spd);
	if (t->d)
		strafe_right(t, move_spd);
}
