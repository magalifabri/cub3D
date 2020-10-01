#include "cub3d.h"

void ft_putpxl(t_cub3d *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr[0] + (y * data->line_len[0] + x * (data->bpp[0] / 8));
    *(unsigned int *)dst = color;
}

void draw_background(t_cub3d *t, int sky, int floor)
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

int run_game(t_cub3d *t)
{
    while (t->game == 1)
    {
        int i;
        double z_buf[t->win_w];
        
        // play_music();
        draw_background(t, t->colors[1], t->colors[0]);
        // draw_floors(t);
        // draw_skybox(t);
        // draw_skybox2(t);
        i = -1;
        while (++i < t->win_w)
            z_buf[i] = draw_walls(t, i);
        if (t->sprite_n != 0)
            draw_sprites(t, z_buf);
        mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
        move(t);
        t->mouse_move = 0;
        return (0);
    }
    return (0);
}

void            get_textures(t_cub3d *t)
{
    int     img_width[8];
    int     img_height[8];
    unsigned int texel;
    unsigned int i;

    t->tex_path[5] = "./textures/night_sky_long.xpm"; // skybox
    t->tex_path[6] = "./textures/dirt_dark.xpm"; // floor
    t->tex_path[7] = "./textures/clouds4.xpm"; // moving skybox overlay
    i = 1;
    while (i < 9)
    {
        t->texture[i - 1] = mlx_xpm_file_to_image(t->mlx, t->tex_path[i - 1], &img_width[i - 1], &img_height[i - 1]);
        t->addr[i] = mlx_get_data_addr(t->texture[i - 1], &t->bpp[i], &t->line_len[i], &t->endian[i]);
        texel = ft_getpxl(t->addr[i], t->line_len[i], t->bpp[i], 2, 2);
        printf("%u\n", texel);
        i++;
    }
}

int main(void)
{
    t_cub3d t;

    ft_init(&t);
    parse_cub_file(&t);
    t.mlx = mlx_init();
    t.win = mlx_new_window(t.mlx, t.win_w, t.win_h, "Hello world!");
    t.img = mlx_new_image(t.mlx, t.win_w, t.win_h);
    t.addr[0] = mlx_get_data_addr(t.img, &t.bpp[0], &t.line_len[0], &t.endian[0]);
    mlx_mouse_hide();
    mlx_mouse_move(t.win, t.win_w / 2, t.win_h / 2);
    get_textures(&t);
    mlx_hook(t.win, 2, 1L << 0, keypress_hook, &t);
    mlx_hook(t.win, 3, 1L << 1, keyrelease_hook, &t);
    mlx_hook(t.win, 6, 1L << 6, mouse_move_hook, &t);
    mlx_hook(t.win, 17, 0, exit_hook, &t);
    mlx_loop_hook(t.mlx, run_game, &t);
    mlx_loop(t.mlx);
    return (0);
}
