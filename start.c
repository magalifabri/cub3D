#include "cub3d.h"

void            ft_putpxl(cub3d *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr[0] + (y * data->line_len[0] + x * (data->bpp[0] / 8));
    *(unsigned int*)dst = color;
}

void            ft_background(cub3d *t, int sky, int floor)
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

int ft_pick_texture(cub3d *t, char face)
{
    int tex;

    if (face == 'y' && (t->r_dir >= 0 && t->r_dir <= 180))
        tex = 1; // south-facing
    else if (face == 'y')
        tex = 2; // noth-facing
    else if (face == 'x' && (t->r_dir >= 90 && t->r_dir <= 270))
        tex = 3; // east-facing
    else
        tex = 4; // west-facing
    return (tex);
}

int             ft_walls(cub3d *t, int i)
{
    int j;
    int tex_x;
    double tex_y_incr;
    static int tex;

    t->r_dir = (t->r_dir < 0) ? (t->r_dir + 360) : (t->r_dir);
    t->r_dir = (t->r_dir > 360) ? (t->r_dir - 360) : (t->r_dir);
    raycaster_main(t);
    tex_x = (t->face == 'y') ? (t->tex_x1) : (t->tex_x2);    
    t->d1 *= cos((t->r_dir - t->p_dir) * M_PI / 180);
    t->wsh = ((64.0 / t->d1) * (t->win_w / 2) / tan((t->fov / 2) * M_PI / 180));    
    tex_y_incr = (64.00 / t->wsh);
    (t->wsh > t->win_h || t->d1 == 0) && (t->wsh = t->win_h);
    tex = (t->face != 'z') ? (ft_pick_texture(t, t->face)) : (tex);
    j = -1;
    while (++j < t->wsh / 2)
        ft_putpxl(t, i, (t->win_h / 2) - j, ft_getpxl(t->addr[tex], t->line_len[tex],
        t->bpp[tex], tex_x, 32 - (tex_y_incr * j)));
    j = -1;
    while (++j < t->wsh / 2)
        ft_putpxl(t, i, (t->win_h / 2) + j, ft_getpxl(t->addr[tex], t->line_len[tex],
        t->bpp[tex], tex_x, 32 + (tex_y_incr * j)));
    // t->r_dir -= ((double)t->fov / (double)t->win_w);
    return (0);
}

void             put_sprites(cub3d *t, int i)
{
    int j;
    double tex_y_incr;
    static int tex;
    unsigned int texel;

    if (!(raycaster_sprites_main(t)))
    {
        t->r_dir -= ((double)t->fov / (double)t->win_w);
        return ;
    }
    if (t->tex_x1 < 0 || t->tex_x1 > 63)
        return ;
    t->tex_x1 = (t->side == 'l') ? 32 - t->tex_x1 : 32 + t->tex_x1;
    // texel = 0;
    // if (t->tex_x1 < 0 || t->tex_x1 > 64)
    //     texel = 4278190080;
    // if (i == 0)
    //     printf("%d\n", t->tex_x1);
    if (i == 0)
        printf("%d\n", t->tex_x1);
    
    // t->d1 *= cos((t->r_dir - t->p_dir) * M_PI / 180);
    t->wsh = ((64.0 / t->d1) * (t->win_w / 2) / tan((t->fov / 2) * M_PI / 180));    
    tex_y_incr = (64.00 / t->wsh);
    (t->wsh > t->win_h || t->d1 == 0) && (t->wsh = t->win_h);
    tex = 5;
    j = -1;
    while (++j < t->wsh / 2)
    {
        texel = ft_getpxl(t->addr[tex], t->line_len[tex],
        t->bpp[tex], t->tex_x1, 32 - (tex_y_incr * j));
        if (texel != 4278190080 && (t->tex_x1 >= 0 && t->tex_x1 < 64))
            ft_putpxl(t, i, (t->win_h / 2) - j, texel);
    }
    j = -1;
    while (++j < t->wsh / 2)
    {
        texel = ft_getpxl(t->addr[tex], t->line_len[tex],
        t->bpp[tex], t->tex_x1, 32 + (tex_y_incr * j));
        if (texel != 4278190080 && (t->tex_x1 >= 0 && t->tex_x1 < 64))
            ft_putpxl(t, i, (t->win_h / 2) + j, texel);
    }
    t->r_dir -= ((double)t->fov / (double)t->win_w);
}

int             ft_game(cub3d *t)
{
    while (t->game == 1)
    {
        int i;

        ft_background(t, t->colors[1], t->colors[0]);
        t->r_dir = (double)t->p_dir + (double)(t->fov / 2);
        i = 0;
        while (i < t->win_w)
        {
            ft_walls(t, i);
            put_sprites(t, i);
            i++;
        }
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
    mlx_hook(t.win, 2, 1L<<0, ft_keypress, &t);
    mlx_hook(t.win, 3, 1L<<1, ft_keyrelease, &t);
    mlx_hook(t.win, 17, 0, exit_hook, &t);
    mlx_loop_hook(t.mlx, ft_game, &t);
    mlx_loop(t.mlx);
    return (0);
}
