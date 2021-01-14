/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:51:07 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/14 15:11:59 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_music(t_cub3d *t)
{
	static double time_start_music;

	if (time_start_music == 0 || ((double)(t->time_now - time_start_music)
	/ (double)CLOCKS_PER_SEC >= 216.0))
	{
		if (t->music_playing)
			system("killall afplay");
		system("afplay -v 0.10 audio/music2.mp3 & exit");
		t->music_playing = 1;
		time_start_music = t->time_now;
	}
}

void	death(t_cub3d *t)
{
	system("afplay -v 0.20 audio/scream.mp3 & exit");
	ft_printf(B_RED"YOU ARE SPIDER FOOD! >:)"RESET"\n");
	sleep(1);
	exit_cub3d(t);
}

void	stop_music(t_cub3d *t)
{
	system("killall afplay");
	t->music_playing = 0;
}
