#include "cub3d.h"

#include "cub3d.h"

typedef struct s_put_sprites_variables
{
    double sprite_y;
    double sprite_x;
    double sprite_x2;
    double sprite_y2;
    double inv_det;
    double transform_x;
    double transform_y;
    int sprite_scrn_x;
    int sprite_h;
    int draw_start_y;
    int draw_end_y;
    int sprite_w;
    int draw_start_x;
    int draw_end_x;
    unsigned int texel;
    int tex_x;
    int tex_y;
    int d;
} t_spr;

static void sort_sprites(t_cub3d *t)
{
    t_sprite tmp;
    int i;
    int j;

    i = -1;
    while (++i < t->sprite_n)
        t->spr[i].dis = ((t->p_x - t->spr[i].x) * (t->p_x - t->spr[i].x) + (t->p_y - t->spr[i].y) * (t->p_y - t->spr[i].y));
    i = 0;
    j = 1;
    while (t->spr[i + 1].y != t->map_h)
    {
        while (t->spr[j].y != t->map_h)
        {
            if (t->spr[i].dis < t->spr[j].dis)
            {
                tmp = t->spr[j];
                t->spr[j] = t->spr[i];
                t->spr[i] = tmp;
            }
            j++;
        }
        i++;
        j = i + 1;
    }
}

static void make_calculations_2(t_cub3d *t, t_spr *s, int x, int y, int frame)
{
    s->d = (y)*256 - t->win_h * 128 + s->sprite_h * 128;
    s->tex_y = ((s->d * 64) / s->sprite_h) / 256;
    s->texel = ft_getpxl(t->addr[frame + 10], t->line_len[frame + 10],
    t->bpp[frame + 10], s->tex_x, s->tex_y);
    s->texel = shader(s->texel, s->transform_y);
    if (s->texel != 4278190080 && (t->tex_x1 >= 0 && t->tex_x1 < 64))
        ft_putpxl(t, x, y, s->texel); 
}

static void make_calculations_1(t_cub3d *t, t_spr *s)
{
    s->sprite_x2 = s->sprite_x - t->p_x; //translate sprite position to relative to camera
    s->sprite_y2 = s->sprite_y - t->p_y;
    s->inv_det = 1.0 / (t->plane_x * t->p_dir_y - t->p_dir_x * t->plane_y); //required for correct matrix multiplication
    s->transform_x = s->inv_det * (t->p_dir_y * s->sprite_x2 - t->p_dir_x * s->sprite_y2);
    s->transform_y = s->inv_det * (-t->plane_y * s->sprite_x2 + t->plane_x * s->sprite_y2); //this is actually the depth inside the screen, that what Z is in 3D
    s->sprite_scrn_x = (int)((t->win_w / 2) * (1 + s->transform_x / s->transform_y));
    //calculate height of the sprite on screen
    s->sprite_h = abs((int)(t->win_h / (s->transform_y))); //using 'transform_y' instead of the real distance prevents fisheye
    s->draw_start_y = -s->sprite_h / 2 + t->win_h / 2; //calculate lowest and highest pixel to fill in current x
    if (s->draw_start_y < 0)
        s->draw_start_y = 0;
    s->draw_end_y = s->sprite_h / 2 + t->win_h / 2;
    if (s->draw_end_y >= t->win_h)
        s->draw_end_y = t->win_h - 1;
    s->sprite_w = abs((int)(t->win_h / (s->transform_y))); //calculate width of the sprite
    s->draw_start_x = -s->sprite_w / 2 + s->sprite_scrn_x;
    if (s->draw_start_x < 0)
        s->draw_start_x = 0;
    s->draw_end_x = s->sprite_w / 2 + s->sprite_scrn_x;
    if (s->draw_end_x >= t->win_w)
        s->draw_end_x = t->win_w - 1;
}

void draw_enemy(t_cub3d *t, double *z_buf)
{
    t_spr s;
    int i;
    int x;
    int y;
    static double last_frame_switch[10];
    static int frame[10];
	clock_t	actual_time;

    // write(1, "a\n", 2);
	actual_time = clock();
    sort_sprites(t);
    i = 0;
    while (t->spr[i].y != t->map_h)
    {
        s.sprite_y = t->spr[i].y + 0.5;
        s.sprite_x = t->spr[i++].x + 0.5;
        make_calculations_1(t, &s);
        x = s.draw_start_x - 1;
        while (++x < s.draw_end_x)
        {
            if (x == t->win_w / 2 && t->shoot == 1)
                printf("hit!\n");
            s.tex_x = (int)(256 * (x - (-s.sprite_w / 2 + s.sprite_scrn_x)) * 64 / s.sprite_w) / 256;
            if (s.transform_y > 0 && x > 0 && x < t->win_w && s.transform_y < z_buf[x])
            {
                y = s.draw_start_y - 1;
                while (++y < s.draw_end_y)
                    make_calculations_2(t, &s, x, y, frame[i]);
            }
        }
        if ((double)(actual_time - last_frame_switch[i]) / (double)CLOCKS_PER_SEC > 0.05)
        {
            frame[i]++;
            last_frame_switch[i] = actual_time;
        }
        if (frame[i] > 3)
            frame[i] = 0;
    }
}

// void draw_enemy(t_cub3d *p)
// {
//     int scrn_x;
//     int scrn_y;
//     int x;
//     int y;
//     double tex_incr;
//     unsigned int texel;
//     static int tex_nbr;
//     static double last_sprite_frame_switch;
// 	clock_t	actual_time;

// 	actual_time = clock();
//     scrn_x = p->e_x * p->scale;
//     scrn_y = p->e_y * p->scale;
//     tex_incr = 64.0 / (double)p->scale;
//     x = -1;
//     while (++x < p->scale)
//     {
//         y = -1;
//         while (++y < p->scale)
//         {
//             texel = getpxl(p->addr[tex_nbr], p->line_len[tex_nbr], p->bpp[tex_nbr], x * tex_incr, y * tex_incr);
//             if (texel != 4278190080)
//                 draw_pxl(p, scrn_x + x, scrn_y + y, texel);
//         }
//     }
//     if ((double)(actual_time - last_sprite_frame_switch) / (double)CLOCKS_PER_SEC > 0.05)
//     {
//         tex_nbr++;
//         last_sprite_frame_switch = actual_time;
//     }
//     if (tex_nbr > 12)
//         tex_nbr = 9;
// }