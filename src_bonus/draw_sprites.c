/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:13:39 by mfabri            #+#    #+#             */
/*   Updated: 2020/05/01 21:04:31 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_sprites(t_cub3d *t)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = -1;
	while (++i < t->sprite_n)
		t->spr[i].dis = ((t->p_x - t->spr[i].x) * (t->p_x - t->spr[i].x)
		+ (t->p_y - t->spr[i].y) * (t->p_y - t->spr[i].y));
	i = 0;
	j = 1;
	while (i + 1 < t->sprite_n)
	{
		while (j < t->sprite_n)
		{
			if (t->spr[i].dis < t->spr[j].dis)
			{
				tmp = t->spr[j];
				t->spr[j] = t->spr[i];
				t->spr[i] = tmp;
			}
			j++;
		}
		i++;
		j = i + 1;
	}
}

static void	make_calculations_2(t_cub3d *t, t_spr *s, int frame, double z_buf)
{
	int	y;

	if (s->transform_y > 0 && s->x > 0 && s->x < t->win_w
	&& s->transform_y < z_buf)
	{
		y = s->draw_start_y - 1;
		while (++y < s->draw_end_y)
		{
			s->d = y * 256 - t->win_h * 128 + s->sprite_h * 128;
			s->tex_y = ((s->d * 64) / s->sprite_h) / 256;
			s->texel = ft_getpxl(t, frame, s->tex_x, s->tex_y);
			if (t->spr[s->i].hit > 0)
				s->texel = shader_red(s->texel);
			s->texel = shader(s->texel, s->transform_y);
			if (s->texel != INVISIBLE)
				ft_putpxl(t, s->x, y, s->texel);
		}
	}
}

static void	make_calculations_1(t_cub3d *t, t_spr *s)
{
	s->sprite_x2 = s->sprite_x - t->p_x;
	s->sprite_y2 = s->sprite_y - t->p_y;
	s->inv_det = 1.0 / (t->plane_x * t->p_dir_y - t->p_dir_x * t->plane_y);
	s->transform_x =
	s->inv_det * (t->p_dir_y * s->sprite_x2 - t->p_dir_x * s->sprite_y2);
	s->transform_y =
	s->inv_det * (-t->plane_y * s->sprite_x2 + t->plane_x * s->sprite_y2);
	s->sprite_scrn_x =
	(int)((t->win_w / 2) * (1 + s->transform_x / s->transform_y));
	s->sprite_h = abs((int)(t->win_h / (s->transform_y)));
	s->draw_start_y = -s->sprite_h / 2 + t->win_h / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_h / 2 + t->win_h / 2;
	if (s->draw_end_y >= t->win_h)
		s->draw_end_y = t->win_h - 1;
	s->sprite_w = abs((int)(t->win_h / (s->transform_y)));
	s->draw_start_x = -s->sprite_w / 2 + s->sprite_scrn_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_w / 2 + s->sprite_scrn_x;
	if (s->draw_end_x >= t->win_w)
		s->draw_end_x = t->win_w - 1;
}

void		draw_sprites(t_cub3d *t, double *z_buf)
{
	t_spr		s;
	static int	frame[50];

	sort_sprites(t);
	s.i = -1;
	while (++s.i < t->sprite_n)
	{
		if (t->spr[s.i].type != '0')
		{
			s.sprite_y =
			t->spr[s.i].y + 0.5 + t->spr[s.i].y_draw * t->spr[s.i].mod;
			s.sprite_x =
			t->spr[s.i].x + 0.5 + t->spr[s.i].x_draw * t->spr[s.i].mod;
			make_calculations_1(t, &s);
			frame[s.i] = get_sprite_frame(t, s.i);
			s.x = s.draw_start_x - 1;
			while (++s.x < s.draw_end_x)
			{
				s.tex_x =
				(int)(256 * (s.x - (-s.sprite_w / 2 + s.sprite_scrn_x))
				* 64 / s.sprite_w) / 256;
				make_calculations_2(t, &s, frame[s.i], z_buf[s.x]);
			}
		}
	}
}
