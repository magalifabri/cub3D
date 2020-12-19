/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:12:12 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/27 14:33:45 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		make_calculations(t_cub3d *t, t_psv *s, int x)
{
	t->scrn_x = 2 * x / (double)t->win_w - 1;
	s->r_dir_x = t->p_dir_x + (t->plane_x * t->scrn_x);
	s->r_dir_y = t->p_dir_y + (t->plane_y * t->scrn_x);
	s->r_degree = atan(s->r_dir_y / s->r_dir_x) * 180 / M_PI;
	if (s->r_dir_x >= 0 && s->r_dir_y <= 0)
		s->r_degree = s->r_degree + 90;
	else if (s->r_dir_x > 0 && s->r_dir_y > 0)
		s->r_degree = s->r_degree + 90;
	else if (s->r_dir_x < 0 && s->r_dir_y > 270)
		s->r_degree = s->r_degree + 0;
	else if (s->r_dir_x < 0 && s->r_dir_y < 270)
		s->r_degree = s->r_degree + 270;
}

/*
** draw_skybox() adds a skybox
*/

void			draw_skybox(t_cub3d *t)
{
	t_psv	s;
	int		x;
	int		y;

	x = -1;
	while (++x < t->win_w)
	{
		make_calculations(t, &s, x);
		s.tex_x = (1024 / 360.0) * (s.r_degree);
		if (s.tex_x > 1024)
			return ;
		s.tex_y_incr = (128.0 / (t->win_h / 2));
		y = -1;
		while (++y < t->win_h / 2)
			ft_putpxl(t, x, y, ft_getpxl(t, 5, s.tex_x, y * s.tex_y_incr));
	}
}

/*
** draw_skybox2() draws moving clouds on top of the skybox above
*/

void			draw_skybox2(t_cub3d *t)
{
	t_psv			s;
	int				x;
	int				y;
	static double	degree_incr;
	unsigned int	texel;

	x = -1;
	while (++x < t->win_w)
	{
		make_calculations(t, &s, x);
		s.tex_x = (1024.0 / 360.0) * (s.r_degree + degree_incr);
		s.tex_y_incr = (128.0 / (t->win_h / 2));
		y = -1;
		while (++y < t->win_h / 2)
		{
			texel = ft_getpxl(t, 7, s.tex_x, y * s.tex_y_incr);
			if (texel != INVISIBLE)
				ft_putpxl(t, x, y, texel);
		}
	}
	degree_incr = degree_incr + 0.05;
	degree_incr = (degree_incr > 360.0) ? 0 : degree_incr;
}
