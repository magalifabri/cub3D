/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:00:14 by mfabri            #+#    #+#             */
/*   Updated: 2020/04/27 16:02:40 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_and_exit(t_cub3d *t, char *message)
{
	ft_printf(B_RED"Error: %s"RESET"\n", message);
	exit_cub3d(t);
}

void	draw_background(t_cub3d *t, int sky, int floor)
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

void	print_terminal_map(t_cub3d *t)
{
	int y;
	int x;

	x = 0;
	y = 0;
	while (y < t->map_h)
	{
		while (x <= t->map_w)
		{
			ft_printf("%c", t->map[y][x]);
			x++;
		}
		ft_printf("\n");
		x = 0;
		y++;
	}
}

double	get_distance(int y_dest, int x_dest, int y_src, int x_src)
{
	double	x_dif;
	double	y_dif;
	double	angle;
	double	distance;

	x_dif = x_src - x_dest;
	y_dif = y_src - y_dest;
	angle = fabs(atan(y_dif / x_dif));
	if ((angle > 0.25 && angle < 0.75) || (angle > 1.25 && angle < 1.75))
		distance = y_dif / sin(angle);
	else
		distance = x_dif / cos(angle);
	return (fabs(distance));
}

void	play_music(t_cub3d *t)
{
	static double time_start_music;

	if (time_start_music == 0 || ((double)(t->time_now - time_start_music)
	/ (double)CLOCKS_PER_SEC >= 216.0))
	{
		system("killall afplay");
		system("afplay -v 0.10 audio/music2.mp3 & exit");
		time_start_music = t->time_now;
	}
}
