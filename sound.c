#include "cub3d.h"

void	play_music(t_cub3d *t)
{
	static double time_start_music;

	if (time_start_music == 0 || ((double)(t->time_now - time_start_music)
	/ (double)CLOCKS_PER_SEC >= 216.0))
	{
		printf("%lu, %f, %i, %f\n", t->time_now, time_start_music, CLOCKS_PER_SEC, (double)(t->time_now - time_start_music) / (double)CLOCKS_PER_SEC);
		system("killall afplay");
		system("afplay -v 0.10 audio/music2.mp3 & exit");
		time_start_music = t->time_now;
	}
}
