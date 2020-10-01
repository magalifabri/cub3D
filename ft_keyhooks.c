#include "cub3d.h"

void            ft_move(cub3d *t)
{
    double p_x_tmp;
    double p_y_tmp;
    if (t->w == 1)
    {
        p_y_tmp = t->p_y - sin(t->p_dir * M_PI / 180)*t->spd;
        p_x_tmp = t->p_x + cos(t->p_dir * M_PI / 180)*t->spd;
        if (t->map[(int)p_y_tmp >> 6][(int)p_x_tmp >> 6] != '1')
        {
            t->p_y = p_y_tmp;
            t->p_x = p_x_tmp;
        }
    }
    if (t->s == 1)
    {
        p_y_tmp = t->p_y + sin(t->p_dir * M_PI / 180)*t->spd;
        p_x_tmp = t->p_x - cos(t->p_dir * M_PI / 180)*t->spd;
        if (t->map[(int)p_y_tmp >> 6][(int)p_x_tmp >> 6] != '1')
        {
            t->p_y = p_y_tmp;
            t->p_x = p_x_tmp;
        }
    }
    if (t->l_a == 1)
        t->p_dir = (t->p_dir + 2 > 360) ? (0) : (t->p_dir + 1);
    if (t->r_a == 1)
        t->p_dir = (t->p_dir - 2 < 0) ? (360) : (t->p_dir - 1);
    if (t->a == 1)
    {
        p_y_tmp = t->p_y - sin((t->p_dir + 90 > 360 ? t->p_dir - 270 : t->p_dir + 90) * M_PI / 180)*t->spd;
        p_x_tmp = t->p_x + cos((t->p_dir + 90 > 360 ? t->p_dir - 270 : t->p_dir + 90) * M_PI / 180)*t->spd;
        if (t->map[(int)p_y_tmp >> 6][(int)p_x_tmp >> 6] != '1')
        {
            t->p_y = p_y_tmp;
            t->p_x = p_x_tmp;
        }
    }
    if (t->d == 1)
    {
        p_y_tmp = t->p_y - sin((t->p_dir - 90 < 0 ? t->p_dir + 270 : t->p_dir - 90) * M_PI / 180)*t->spd;
        p_x_tmp = t->p_x + cos((t->p_dir - 90 < 0 ? t->p_dir + 270 : t->p_dir - 90) * M_PI / 180)*t->spd;
        if (t->map[(int)p_y_tmp >> 6][(int)p_x_tmp >> 6] != '1')
        {
            t->p_y = p_y_tmp;
            t->p_x = p_x_tmp;
        }
    }
    return ;
}

int             ft_keypress(int keycode, cub3d *t)
{
    double p_x_tmp;
    double p_y_tmp;

    // printf("key = %d\n", keycode);
    p_x_tmp = t->p_x;
    p_y_tmp = t->p_y;
    if (keycode == 53) // esc
        exit(0);
    else if (keycode == 123) // left arrow: turn left
        t->l_a = 1;
    else if (keycode == 124) // right arrow: turn right
        t->r_a = 1;
    else if (keycode == 13) // w: forwards
        t->w = 1;
    else if (keycode == 1) // s: backwards
        t->s = 1;
    else if (keycode == 0) // a: strafe left
        t->a = 1;
    else if (keycode == 2) // d: strage right
        t->d = 1;
    return (0);
}

int             ft_keyrelease(int keycode, cub3d *t)
{
    if (keycode == 123)
        t->l_a = 0;
    if (keycode == 124)
        t->r_a = 0;
    if (keycode == 13)
        t->w = 0;
    if (keycode == 1)
        t->s = 0;
    if (keycode == 0)
        t->a = 0;
    if (keycode == 2)
        t->d = 0;
    return (0);
}

int             exit_hook(int keycode, cub3d *t)
{
    exit(0);
    t->w = t->w;
    return (keycode);
}
