/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui_elements_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:15:16 by mfabri            #+#    #+#             */
/*   Updated: 2020/04/27 16:15:37 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	draw_hearts_part_2(t_cub3d *t, int x_start, int frame)
{
	int				x;
	int				y;
	unsigned int	texel;

	y = -1;
	while (++y < 32)
	{
		x = -1;
		while (++x < 32)
		{
			texel = ft_getpxl(t, 34 + frame, x / 2, y / 2);
			if (texel != INVISIBLE)
				ft_putpxl(t, x_start + x, y, texel);
		}
	}
	return (x_start -= 32);
}

void		draw_hearts(t_cub3d *t)
{
	int				heart;
	int				x_start;
	static double	time_frame_swp;
	static int		frame;

	heart = -1;
	x_start = t->win_w - (32 * 1 + heart);
	while (++heart < t->p_health)
		x_start = draw_hearts_part_2(t, x_start, frame);
	if ((double)(t->time_now - time_frame_swp) / (double)CLOCKS_PER_SEC > 0.1)
	{
		frame++;
		time_frame_swp = t->time_now;
	}
	if (frame > 3)
		frame = 0;
}
