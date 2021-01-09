/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:16:22 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/09 18:57:08 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	make_calculations_3(t_cub3d *t, t_pwv *w)
{
	w->line_height = (int)(t->win_h / w->perp_wall_dist);
	w->draw_start = -w->line_height / 2 + t->win_h / 2;
	w->draw_start = (w->draw_start < 0) ? (0) : (w->draw_start);
	w->draw_end = w->line_height / 2 + t->win_h / 2;
	w->draw_end = (w->draw_end >= t->win_h) ? (t->win_h - 1) : (w->draw_end);
	if (w->r_dir_x >= 0 && w->side == 0)
		w->tex_nbr = 0;
	else if (w->r_dir_x < 0 && w->side == 0)
		w->tex_nbr = 1;
	else if (w->r_dir_y >= 0 && w->side == 1)
		w->tex_nbr = 2;
	else if (w->r_dir_y < 0 && w->side == 1)
		w->tex_nbr = 3;
	w->wall_x = (w->side == 0) ? (t->p_y + w->perp_wall_dist * w->r_dir_y)
	: (t->p_x + w->perp_wall_dist * w->r_dir_x);
	w->wall_x -= floor((w->wall_x));
	w->tex_x = (int)(w->wall_x * (double)64);
	if ((w->side == 0 && w->r_dir_x > 0) || (w->side == 1 && w->r_dir_y < 0))
		w->tex_x = 64 - w->tex_x - 1;
	w->step = 1.0 * 64 / w->line_height;
	w->tex_pos = (w->draw_start - t->win_h / 2 + w->line_height / 2) * w->step;
}

static void	make_calculations_2(t_cub3d *t, t_pwv *w)
{
	while (w->map_x < t->map_w && w->map_x > 0 && w->map_y < t->map_h
	&& w->map_y > 0 && t->map[w->map_y][w->map_x] != '1')
	{
		if (w->side_dist_x < w->side_dist_y)
		{
			w->side_dist_x += w->delta_dist_x;
			w->map_x += w->step_x;
			w->side = 0;
		}
		else
		{
			w->side_dist_y += w->delta_dist_y;
			w->map_y += w->step_y;
			w->side = 1;
		}
	}
	w->perp_wall_dist = (w->side == 0)
	? (w->map_x - t->p_x + (1 - w->step_x) / 2) / w->r_dir_x
	: (w->map_y - t->p_y + (1 - w->step_y) / 2) / w->r_dir_y;
}

static void	make_calculations_1(t_cub3d *t, t_pwv *w)
{
	if (w->r_dir_x < 0)
	{
		w->step_x = -1;
		w->side_dist_x = (t->p_x - w->map_x) * w->delta_dist_x;
	}
	else
	{
		w->step_x = 1;
		w->side_dist_x = (w->map_x + 1.0 - t->p_x) * w->delta_dist_x;
	}
	if (w->r_dir_y < 0)
	{
		w->step_y = -1;
		w->side_dist_y = (t->p_y - w->map_y) * w->delta_dist_y;
	}
	else
	{
		w->step_y = 1;
		w->side_dist_y = (w->map_y + 1.0 - t->p_y) * w->delta_dist_y;
	}
}

double		draw_walls(t_cub3d *t, int x)
{
	t_pwv	w;
	int		y;

	t->scrn_x = 2 * x / (double)t->win_w - 1;
	w.r_dir_x = t->p_dir_x + (t->plane_x * t->scrn_x);
	w.r_dir_y = t->p_dir_y + (t->plane_y * t->scrn_x);
	w.map_x = (int)t->p_x;
	w.map_y = (int)t->p_y;
	w.delta_dist_x = fabs(1 / w.r_dir_x);
	w.delta_dist_y = fabs(1 / w.r_dir_y);
	make_calculations_1(t, &w);
	make_calculations_2(t, &w);
	make_calculations_3(t, &w);
	y = -1;
	while (++y < w.line_height && y < t->win_h)
	{
		w.texel = ft_getpxl(t, w.tex_nbr, w.tex_x, w.tex_pos + (w.step * y));
		w.texel = shader(w.texel, w.perp_wall_dist);
		if (w.texel != INVISIBLE)
		{
			ft_putpxl(t, x, w.draw_start + y, w.texel);
		}
	}
	return (w.perp_wall_dist);
}
