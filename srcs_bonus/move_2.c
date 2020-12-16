/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:25:30 by mfabri            #+#    #+#             */
/*   Updated: 2020/04/27 16:25:31 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_left(t_cub3d *t, double rot_spd)
{
	double	old_p_dir_x;
	double	old_plane_x;

	if (t->l_a == 1 && t->r_a == 0)
	{
		old_p_dir_x = t->p_dir_x;
		t->p_dir_x = t->p_dir_x * cos(-rot_spd) - t->p_dir_y * sin(-rot_spd);
		t->p_dir_y = old_p_dir_x * sin(-rot_spd) + t->p_dir_y * cos(-rot_spd);
		old_plane_x = t->plane_x;
		t->plane_x = t->plane_x * cos(-rot_spd) - t->plane_y * sin(-rot_spd);
		t->plane_y = old_plane_x * sin(-rot_spd) + t->plane_y * cos(-rot_spd);
	}
	if (t->mouse_move < 0)
	{
		rot_spd *= (t->mouse_move * 0.5);
		old_p_dir_x = t->p_dir_x;
		t->p_dir_x = t->p_dir_x * cos(rot_spd) - t->p_dir_y * sin(rot_spd);
		t->p_dir_y = old_p_dir_x * sin(rot_spd) + t->p_dir_y * cos(rot_spd);
		old_plane_x = t->plane_x;
		t->plane_x = t->plane_x * cos(rot_spd) - t->plane_y * sin(rot_spd);
		t->plane_y = old_plane_x * sin(rot_spd) + t->plane_y * cos(rot_spd);
	}
}

void	turn_right(t_cub3d *t, double rot_spd)
{
	double	old_p_dir_x;
	double	old_plane_x;

	if (t->r_a == 1 && t->l_a == 0)
	{
		old_p_dir_x = t->p_dir_x;
		t->p_dir_x = t->p_dir_x * cos(rot_spd) - t->p_dir_y * sin(rot_spd);
		t->p_dir_y = old_p_dir_x * sin(rot_spd) + t->p_dir_y * cos(rot_spd);
		old_plane_x = t->plane_x;
		t->plane_x = t->plane_x * cos(rot_spd) - t->plane_y * sin(rot_spd);
		t->plane_y = old_plane_x * sin(rot_spd) + t->plane_y * cos(rot_spd);
	}
	if (t->mouse_move > 0)
	{
		rot_spd *= (t->mouse_move * 0.5);
		old_p_dir_x = t->p_dir_x;
		t->p_dir_x = t->p_dir_x * cos(rot_spd) - t->p_dir_y * sin(rot_spd);
		t->p_dir_y = old_p_dir_x * sin(rot_spd) + t->p_dir_y * cos(rot_spd);
		old_plane_x = t->plane_x;
		t->plane_x = t->plane_x * cos(rot_spd) - t->plane_y * sin(rot_spd);
		t->plane_y = old_plane_x * sin(rot_spd) + t->plane_y * cos(rot_spd);
	}
}
