#include "cub3d.h"

void ft_putpxl(t_cub3d *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr[0] + (y * data->line_len[0] + x * (data->bpp[0] / 8));
    *(unsigned int *)dst = color;
}

void ft_background(t_cub3d *t, int sky, int floor)
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

void play_music(void)
{
	// system("afplay -v 0.30 music2.mp3");
    static double last_start_song;
	long	clk_tck;
	clock_t	actual_time;

	actual_time = clock();
	clk_tck = CLOCKS_PER_SEC;
    // write(1, "!\n", 2);
    // printf("%lu, %f, %ld, %f\n", actual_time, last_start_song, clk_tck, (double)(actual_time - last_start_song) / (double)clk_tck);
	if (last_start_song == 0 || ((double)(actual_time - last_start_song) / (double)clk_tck >= 216.0))
	{
        // write(1, "?\n", 2);
        printf("%lu, %f, %ld, %f\n", actual_time, last_start_song, clk_tck, (double)(actual_time - last_start_song) / (double)clk_tck);
        system("killall afplay");
        system("afplay -v 0.10 music2.mp3 & exit");
        // system("afplay -v 0.10 music2.mp3 & exit &>/dev/null &");
        last_start_song = actual_time;
    }
    // system("afplay -v 0.30 music2.mp3 &>/dev/null &");
}

int run_game(t_cub3d *t)
{
    while (t->game == 1)
    {
        int i;
        double z_buf[t->win_w];

        play_music();
        ft_background(t, t->colors[1], t->colors[0]);
        put_floors(t);
        put_skybox(t);
        put_skybox2(t);
        i = -1;
        while (++i < t->win_w)
            z_buf[i] = ft_walls(t, i);
        if (t->sprite_n != 0)
            put_sprites(t, z_buf);
        mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
        ft_move(t);
        return (0);
    }
    return (0);
}

int main(void)
{
    t_cub3d t;


    ft_init(&t);
    ft_cub_file_parser(&t);
    t.mlx = mlx_init();
    t.win = mlx_new_window(t.mlx, t.win_w, t.win_h, "Hello world!");
    t.img = mlx_new_image(t.mlx, t.win_w, t.win_h);
    t.addr[0] = mlx_get_data_addr(t.img, &t.bpp[0], &t.line_len[0], &t.endian[0]);
    get_textures(&t);
    mlx_hook(t.win, 2, 1L << 0, ft_keypress, &t);
    mlx_hook(t.win, 3, 1L << 1, ft_keyrelease, &t);
    // mlx_hook(t.win, 6, 1L << 6, mouse_move_hook, &t);
    mlx_hook(t.win, 17, 0, exit_hook, &t);
    mlx_loop_hook(t.mlx, run_game, &t);
    mlx_loop(t.mlx);
    system("killall afplay");
    return (0);
}
