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
        if (t->shoot == 1)
            cast_ray(t);
        i = -1;
        while (++i < t->win_w)
            z_buf[i] = draw_walls(t, i);
        if (t->sprite_n != 0)
            draw_enemy(t, z_buf);
        // if (t->sprite_n != 0)
        //     draw_sprites(t, z_buf);
        draw_crosshair(t);
        draw_torch(t);
        draw_gun(t);
        mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
        move(t);
        find_path(t);
        // move_enemy(t);
        t->mouse_move = 0;

        int y = 0;
        int x = 0;
        while (y < t->map_h)
        {
            while (x <= t->map_w)
            {
                printf("%c", t->map[y][x]);
                x++;
            }
            printf("\n");
            x = 0;
            y++;
        }
        
        return (0);
    }
    return (0);
}

void            get_textures(t_cub3d *t)
{
    int     img_width[40];
    int     img_height[40];
    unsigned int texel;
    unsigned int i;

    t->tex_path[5] = "./textures/night_sky_long.xpm"; // skybox
    t->tex_path[6] = "./textures/surfaces/dirt_dark.xpm"; // floor
    t->tex_path[7] = "./textures/clouds4.xpm"; // moving skybox overlay
    t->tex_path[8] = "./textures/sprite_crosshair2.xpm";
    t->tex_path[9] = "./textures/sprite_bat/bat1.2.1.xpm";
    t->tex_path[10] = "./textures/sprite_bat/bat1.2.2.xpm";
    t->tex_path[11] = "./textures/sprite_bat/bat1.2.3.xpm";
    t->tex_path[12] = "./textures/sprite_bat/bat1.2.4.xpm";
    t->tex_path[13] = "./textures/sprite_torch/sprite_torch1.xpm";
    t->tex_path[14] = "./textures/sprite_torch/sprite_torch2.xpm";
    t->tex_path[15] = "./textures/sprite_torch/sprite_torch3.xpm";
    t->tex_path[16] = "./textures/sprite_torch/sprite_torch4.xpm";
    t->tex_path[17] = "./textures/sprite_gun/sprite_gun1.xpm";
    t->tex_path[18] = "./textures/sprite_gun/sprite_gun2.xpm";
    t->tex_path[19] = "./textures/sprite_gun/sprite_gun3.xpm";
    t->tex_path[20] = "./textures/sprite_gun/sprite_gun4.xpm";
    t->tex_path[21] = "./textures/sprite_death/sprite_blood_splatter1.xpm";
    t->tex_path[22] = "./textures/sprite_death/sprite_blood_splatter2.xpm";
    t->tex_path[23] = "./textures/sprite_spider/walk/sprite_spiderv3.1.xpm";
    t->tex_path[24] = "./textures/sprite_spider/walk/sprite_spiderv3.2.xpm";
    t->tex_path[25] = "./textures/sprite_spider/walk/sprite_spiderv3.3.xpm";
    t->tex_path[26] = "./textures/sprite_spider/walk/sprite_spiderv3.4.xpm";
    t->tex_path[27] = "./textures/sprite_spider/walk/sprite_spiderv3.5.xpm";
    t->tex_path[28] = "./textures/sprite_spider/walk/sprite_spiderv3.6.xpm";
    t->tex_path[29] = "./textures/sprite_spider/attack/sprite_spider_attack1.xpm";
    t->tex_path[30] = "./textures/sprite_spider/attack/sprite_spider_attack2.xpm";
    t->tex_path[31] = "./textures/sprite_spider/attack/sprite_spider_attack3.xpm";
    t->tex_path[32] = "./textures/sprite_spider/attack/sprite_spider_attack4.xpm";
    t->tex_path[33] = "./textures/sprite_spider/attack/sprite_spider_attack5.xpm";
    // t->tex_path[29] = "./textures/sprite_spider/sprite_spider_hit.xpm";
    i = 1;
    while (i < 31)
    {
        t->texture[i - 1] = mlx_xpm_file_to_image(t->mlx, t->tex_path[i - 1], &img_width[i - 1], &img_height[i - 1]);
        t->addr[i] = mlx_get_data_addr(t->texture[i - 1], &t->bpp[i], &t->line_len[i], &t->endian[i]);
        texel = ft_getpxl(t->addr[i], t->line_len[i], t->bpp[i], 2, 2);
        printf("texture %d, %u\n", i, texel);
        i++;
    }
    printf("loading textures complete\n");
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
    t.prev_mouse_x = t.win_w / 2;
    get_textures(&t);
    mlx_hook(t.win, 2, 1L << 0, keypress_hook, &t);
    mlx_hook(t.win, 3, 1L << 1, keyrelease_hook, &t);
    mlx_hook(t.win, 6, 1L << 6, mouse_move_hook, &t);
    mlx_hook(t.win, 17, 0, exit_hook, &t);
    mlx_loop_hook(t.mlx, run_game, &t);
    mlx_loop(t.mlx);
    return (0);
}
