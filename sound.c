#include "cub3d.h"

void play_music(void)
{
    static double last_start_song;
	long	clk_tck;
	clock_t	actual_time;

	actual_time = clock();
	clk_tck = CLOCKS_PER_SEC;
	if (last_start_song == 0 || ((double)(actual_time - last_start_song) / (double)clk_tck >= 216.0))
	{
        printf("%lu, %f, %ld, %f\n", actual_time, last_start_song, clk_tck, (double)(actual_time - last_start_song) / (double)clk_tck);
        system("killall afplay");
        system("afplay -v 0.10 music2.mp3 & exit");
        last_start_song = actual_time;
    }
}