#include "cub3d.h"

void            ft_move(cub3d *t)
{
    double moveSpeed = 0.05;
    if (t->w == 1)
    {
        if (t->map[(int)(t->p_y + t->p_dir_y * moveSpeed)][(int)t->p_x] != '1')
            t->p_y += t->p_dir_y * moveSpeed;
        if (t->map[(int)t->p_y][(int)(t->p_x + t->p_dir_x * moveSpeed)] != '1')
            t->p_x += t->p_dir_x * moveSpeed;
    }
    if (t->s == 1)
    {
        if (t->map[(int)(t->p_y - t->p_dir_y * moveSpeed)][(int)t->p_x] != '1')
            t->p_y -= t->p_dir_y * moveSpeed;
        if (t->map[(int)t->p_y][(int)(t->p_x - t->p_dir_x * moveSpeed)] != '1')
            t->p_x -= t->p_dir_x * moveSpeed;
    }
    if (t->l_a == 1)
    {
        double rotspeed = 0.03;
        double old_p_dir_x = t->p_dir_x;
        t->p_dir_x = t->p_dir_x * cos(-rotspeed) - t->p_dir_y * sin(-rotspeed);
        t->p_dir_y = old_p_dir_x * sin(-rotspeed) + t->p_dir_y * cos(-rotspeed);
        double old_plane_x = t->plane_x;
        t->plane_x = t->plane_x * cos(-rotspeed) - t->plane_y * sin(-rotspeed);
        t->plane_y = old_plane_x * sin(-rotspeed) + t->plane_y * cos(-rotspeed);
    }
    if (t->r_a == 1)
    {
        double rotspeed = 0.03;
        double old_p_dir_x = t->p_dir_x;
        t->p_dir_x = t->p_dir_x * cos(rotspeed) - t->p_dir_y * sin(rotspeed);
        t->p_dir_y = old_p_dir_x * sin(rotspeed) + t->p_dir_y * cos(rotspeed);
        double old_plane_x = t->plane_x;
        t->plane_x = t->plane_x * cos(rotspeed) - t->plane_y * sin(rotspeed);
        t->plane_y = old_plane_x * sin(rotspeed) + t->plane_y * cos(rotspeed);
    }
    if (t->a == 1)
    {
        if (t->map[(int)(t->p_y + (t->p_dir_y * cos(90 * M_PI / 180) - t->p_dir_x * sin(90 * M_PI / 180)) * moveSpeed)][(int)t->p_x] != '1')
            t->p_y += (t->p_dir_y * cos(90 * M_PI / 180) - t->p_dir_x * sin(90 * M_PI / 180)) * moveSpeed;
        if (t->map[(int)t->p_y][(int)(t->p_x + (t->p_dir_y * sin(90 * M_PI / 180) + t->p_dir_x * cos(90 * M_PI / 180)) * moveSpeed)] != '1')
            t->p_x += (t->p_dir_y * sin(90 * M_PI / 180) + t->p_dir_x * cos(90 * M_PI / 180)) * moveSpeed;
    }
    if (t->d == 1)
    {
        if (t->map[(int)(t->p_y - (t->p_dir_y * cos(90 * M_PI / 180) - t->p_dir_x * sin(90 * M_PI / 180)) * moveSpeed)][(int)t->p_x] != '1')
            t->p_y -= (t->p_dir_y  * cos(90 * M_PI / 180) - t->p_dir_x * sin(90 * M_PI / 180)) * moveSpeed;
        if (t->map[(int)t->p_y][(int)(t->p_x - (t->p_dir_y * sin(90 * M_PI / 180) + t->p_dir_x * cos(90 * M_PI / 180)) * moveSpeed)] != '1')
            t->p_x -= (t->p_dir_y * sin(90 * M_PI / 180) + t->p_dir_x * cos(90 * M_PI / 180)) * moveSpeed;
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
