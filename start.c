#include "cub3d.h"

void ft_putpxl(cub3d *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr[0] + (y * data->line_len[0] + x * (data->bpp[0] / 8));
    *(unsigned int *)dst = color;
}

void ft_background(cub3d *t, int sky, int floor)
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

int ft_game(cub3d *t)
{
    while (t->game == 1)
    {
        int i;
        double z_buf[t->win_w];

        ft_background(t, t->colors[1], t->colors[0]);
        
        put_floors(t);
        
        i = 0;
        while (i < t->win_w)
        {
            z_buf[i] = ft_walls(t, i);
            i++;
        }
        put_sprites(t, z_buf);
        mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
        ft_move(t);
        return (0);
    }
    return (0);
}

int main(void)
{
    cub3d t;
    ft_init(&t);
    ft_cub_file_parser(&t);
    t.mlx = mlx_init();
    t.win = mlx_new_window(t.mlx, t.win_w, t.win_h, "Hello world!");
    t.img = mlx_new_image(t.mlx, t.win_w, t.win_h);
    t.addr[0] = mlx_get_data_addr(t.img, &t.bpp[0], &t.line_len[0], &t.endian[0]);
    ft_textures(&t);
    mlx_hook(t.win, 2, 1L << 0, ft_keypress, &t);
    mlx_hook(t.win, 3, 1L << 1, ft_keyrelease, &t);
    mlx_hook(t.win, 17, 0, exit_hook, &t);
    mlx_loop_hook(t.mlx, ft_game, &t);
    mlx_loop(t.mlx);
    return (0);
}
