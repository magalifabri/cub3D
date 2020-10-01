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
        t->spr[i].dis = ((t->p_x - t->spr[i].x) * (t->p_x - t->spr[i].x)
        + (t->p_y - t->spr[i].y) * (t->p_y - t->spr[i].y));    
    i = 0;
    j = 1;
    while (i + 1 < t->sprite_n)
    {
        while (j < t->sprite_n)
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
    // printf("!\n");
    s->d = (y)*256 - t->win_h * 128 + s->sprite_h * 128;
    s->tex_y = ((s->d * 64) / s->sprite_h) / 256;
    s->texel = ft_getpxl(t->addr[frame + 24], t->line_len[frame + 24],
    t->bpp[frame + 24], s->tex_x, s->tex_y);
    // s->texel = shader(s->texel, s->transform_y);
    if (s->texel != 4278190080 && (t->tex_x1 >= 0 && t->tex_x1 < 64))
        ft_putpxl(t, x, y, s->texel);
}
static void death_animation(t_cub3d *t, t_spr *s, int x, int y)
{
    // static int frame;

    s->d = (y)*256 - t->win_h * 128 + s->sprite_h * 128;
    s->tex_y = ((s->d * 64) / s->sprite_h) / 256;
    s->texel = ft_getpxl(t->addr[22], t->line_len[22],
    t->bpp[22], s->tex_x, s->tex_y);
    // s->texel = shader(s->texel, s->transform_y);
    if (s->texel != 4278190080 && (t->tex_x1 >= 0 && t->tex_x1 < 64))
        ft_putpxl(t, x, y, s->texel);
    // frame++;
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
    static double t_o_d[10];
    static int frame[10];
	clock_t	curr_time;

	curr_time = clock();
    sort_sprites(t);
    i = 0;
    while (i < t->sprite_n)
    {
        if (t->spr[i].dead != 1 || (t->spr[i].dead == 1 
        && ((double)(curr_time - t_o_d[i]) / (double)CLOCKS_PER_SEC < 0.1)))
        {
            // printf("%d, %f, %f\n", i, t->spr[i].y_draw, t->spr[i].x_draw);
            s.sprite_y = t->spr[i].y + 0.5 + t->spr[i].y_draw * t->spr[i].counter;
            s.sprite_x = t->spr[i].x + 0.5 + t->spr[i].x_draw * t->spr[i].counter;
            make_calculations_1(t, &s);
            x = s.draw_start_x - 1;
            while (++x < s.draw_end_x)
            {
                if (x == t->win_w / 2 && t->shoot == 1)
                {
                    t->spr[i].dead = 1;
                    // t->shoot = 0;
                    t->map[(int)t->spr[i].y][(int)t->spr[i].x] = '0';
                    t_o_d[i] = clock();
                }
                s.tex_x = (int)(256 * (x - (-s.sprite_w / 2 + s.sprite_scrn_x)) * 64 / s.sprite_w) / 256;
                if (t->spr[i].dead == 1)
                {
                    y = s.draw_start_y - 1;
                    while (++y < s.draw_end_y)
                        death_animation(t, &s, x, y);
                }
                else if (s.transform_y > 0 && x > 0 && x < t->win_w && s.transform_y < z_buf[x])
                {
                    y = s.draw_start_y - 1;
                    while (++y < s.draw_end_y)
                        make_calculations_2(t, &s, x, y, frame[i]);
                }
            }
            if ((double)(curr_time - last_frame_switch[i]) / (double)CLOCKS_PER_SEC > 0.05)
            {
                frame[i]++;
                last_frame_switch[i] = curr_time;
            }
            if (frame[i] > 5)
                frame[i] = 0;
        }
        i++;
    }
}
