#include "cub3d.h"

void draw_red_border(t_cub3d *t)
{
    int x;
    int y;
    // unsigned int texel;
    int width;

    width = 10;
    y = -1;
    while (++y < t->win_h)
    {
        x = -1;
        while (++x < t->win_w)
        {
            if (x < 10 || x > t->win_w - 10)
                ft_putpxl(t, x, y, 0x00FF0000);
        }
    }
}

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

void draw_hearts(t_cub3d *t)
{
    int x;
    int y;
    unsigned int texel;
    int heart;
    int x_start;
    static double last_frame_switch;
    static int frame;
	clock_t	actual_time;

	actual_time = clock();
    heart = 0;
    x_start = t->win_w - (32 * 1 + heart);
    while (heart < t->p_health)
    {
        y = -1;
        while (++y < 32)
        {
            x = -1;
            while (++x < 32)
            {
                texel = ft_getpxl(t->addr[35 + frame], t->line_len[35 + frame], t->bpp[35 + frame], x / 2, y / 2);
                if (texel != 4278190080)
                    ft_putpxl(t, x_start + x, y, texel);
            }
        }
        x_start -= 32;
        heart++;
    }
    if ((double)(actual_time - last_frame_switch) / (double)CLOCKS_PER_SEC > 0.1)
    {
        frame++;
        last_frame_switch = actual_time;
    }
    if (frame > 3)
        frame = 0;
}

void draw_bullets(t_cub3d *t)
{
    int x;
    int y;
    unsigned int texel;
    int bullet;
    int x_start;

    bullet = 0;
    x_start = t->win_w / 3;
    while (bullet < t->p_bullets)
    {
        y = -1;
        while (++y < 32)
        {
            x = -1;
            while (++x < 32)
            {
                texel = ft_getpxl(t->addr[39], t->line_len[39], t->bpp[39], x / 2, y / 2);
                if (texel != 4278190080)
                    ft_putpxl(t, x_start + x, (t->win_h - 37) + y, texel);
            }
        }
        x_start += 20;
        bullet++;
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

