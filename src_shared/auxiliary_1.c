/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:00:20 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/20 12:36:56 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_putpxl(t_cub3d *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	ft_getpxl(t_cub3d *t, int i, int x, int y)
{
	unsigned int	color;
	char			*ptr;

	ptr = t->td[i].addr + (y * t->td[i].line_len + x * (t->td[i].bpp / 8));
	color = *(unsigned int *)ptr;
	return (color);
}

unsigned int	shader_red(unsigned int start_colour)
{
	int	end_colour;
	int	end_colour_r;
	int	end_colour_g;
	int	end_colour_b;

	if (start_colour == INVISIBLE)
		return (start_colour);
	end_colour_r = ((start_colour & 0x00FF0000) >> 16) * 1;
	end_colour_g = ((start_colour & 0x0000FF00) >> 8) * 0.5;
	end_colour_b = (start_colour & 0x000000FF) * 0.5;
	return (end_colour = (end_colour_r << 16)
	+ (end_colour_g << 8) + end_colour_b);
}

unsigned int	shader(unsigned int start_colour, double distance)
{
	int		end_colour;
	int		end_colour_r;
	int		end_colour_g;
	int		end_colour_b;
	double	shade;

	if (start_colour == INVISIBLE || start_colour == 16711680)
		return (start_colour);
	shade = (10 - distance) / 10.0;
	shade = (shade < 0) ? (0.01) : (shade);
	end_colour_r = ((start_colour & 0x00FF0000) >> 16) * shade;
	end_colour_g = ((start_colour & 0x0000FF00) >> 8) * shade;
	end_colour_b = (start_colour & 0x000000FF) * shade;
	return (end_colour = (end_colour_r << 16)
	+ (end_colour_g << 8) + end_colour_b);
}

void			draw_background(t_cub3d *t, int sky, int floor)
{
	int x;
	int y;

	y = 0;
	while (y < (t->win_h / 2))
	{
		x = 0;
		while (x < t->win_w)
			ft_putpxl(t, x++, y, sky);
		y++;
	}
	while (y < t->win_h)
	{
		x = 0;
		while (x < t->win_w)
			ft_putpxl(t, x++, y, floor);
		y++;
	}
}
