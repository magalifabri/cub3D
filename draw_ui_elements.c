#include "cub3d.h"

void draw_crosshair(t_cub3d *t)
{
    int x;
    int y;
    unsigned int texel;

    y = -1;
    while (++y < 32)
    {
        x = -1;
        while (++x < 32)
        {
            texel = ft_getpxl(t->addr[9], t->line_len[9], t->bpp[9], x, y);
            if (texel != 4278190080)
                ft_putpxl(t, ((t->win_w / 2) - 16) + x, ((t->win_h / 2) - 16) + y, texel);
        }
    }
}

void draw_torch(t_cub3d *t)
{
    int x;
    int y;
    unsigned int texel;
    static double last_frame_switch;
    static int frame;
	clock_t	actual_time;

	actual_time = clock();
    y = -1;
    while (++y < 256)
    {
        x = -1;
        while (++x < 256)
        {
            texel = ft_getpxl(t->addr[14 + frame], t->line_len[14 + frame], t->bpp[14 + frame], x / 4, y / 4);
            if (texel != 4278190080)
                ft_putpxl(t, x, y, texel);
        }
    }
    if ((double)(actual_time - last_frame_switch) / (double)CLOCKS_PER_SEC > 0.1)
    {
        frame++;
        last_frame_switch = actual_time;
    }
    if (frame > 3)
        frame = 0;
}

void draw_gun(t_cub3d *t)
{
    int x;
    int y;
    unsigned int texel;
    static double last_frame_switch;
    static int frame;
	clock_t	actual_time;

	actual_time = clock();
    y = -1;
    while (++y < 256)
    {
        x = -1;
        while (++x < 256)
        {
            texel = ft_getpxl(t->addr[18 + frame], t->line_len[18 + frame], t->bpp[18 + frame], x / 4, y / 4);
            if (texel != 4278190080)
                ft_putpxl(t, (t->win_w - 256) + x, (t->win_h - 256) + y, texel);
        }
    }
    if (t->shoot == 1 || frame > 0)
    {
        if ((double)(actual_time - last_frame_switch) / (double)CLOCKS_PER_SEC > 0.1)
        {
            frame++;
            last_frame_switch = actual_time;
        }
        if (frame > 3)
            frame = 0;
        t->shoot = 0;
    }
}

