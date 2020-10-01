#include "cub3d.h"

void move_forward(t_cub3d *t, double moveSpeed)
{
    double new_y;
    double new_x;

    if (t->s == 0)
    {
        new_y = t->p_dir_y * moveSpeed;
        if (t->map[(int)(t->p_y + new_y)][(int)t->p_x] != '1')
            t->p_y += new_y;
        new_x = t->p_dir_x * moveSpeed;
        if (t->map[(int)t->p_y][(int)(t->p_x + new_x)] != '1')
            t->p_x += new_x;
    }
}

void move_backward(t_cub3d *t, double moveSpeed)
{
    double new_y;
    double new_x;

    if (t->w == 0)
    {
        new_y = t->p_dir_y * moveSpeed;
        if (t->map[(int)(t->p_y - new_y)][(int)t->p_x] != '1')
            t->p_y -= new_y;
        new_x = t->p_dir_x * moveSpeed;
        if (t->map[(int)t->p_y][(int)(t->p_x - new_x)] != '1')
            t->p_x -= new_x;
    }
}

void strafe_left(t_cub3d *t, double moveSpeed)
{
    double new_y;
    double new_x;

    if (t->d == 0)
    {
        new_y = t->p_y + (t->p_dir_y * cos(RD(90)) - t->p_dir_x * sin(RD(90))) * moveSpeed;
        if (t->map[(int)new_y][(int)t->p_x] != '1')
            t->p_y = new_y;
        new_x = t->p_x + (t->p_dir_y * sin(RD(90)) + t->p_dir_x * cos(RD(90))) * moveSpeed;
        if (t->map[(int)t->p_y][(int)new_x] != '1')
            t->p_x = new_x;
    }
}

void strafe_right(t_cub3d *t, double moveSpeed)
{
    double new_y;
    double new_x;

    if (t->a == 0)
    {
        new_y = t->p_y - (t->p_dir_y * cos(RD(90)) - t->p_dir_x * sin(RD(90))) * moveSpeed;
        if (t->map[(int)new_y][(int)t->p_x] != '1')
            t->p_y = new_y;
        new_x = t->p_x - (t->p_dir_y * sin(RD(90)) + t->p_dir_x * cos(RD(90))) * moveSpeed;
        if (t->map[(int)t->p_y][(int)new_x] != '1')
            t->p_x = new_x;
    }
}

void turn_left(t_cub3d *t, double rotspeed)
{
    double old_p_dir_x;
    double old_plane_x;

    if (t->r_a == 0)
    {
        old_p_dir_x = t->p_dir_x;
        t->p_dir_x = t->p_dir_x * cos(-rotspeed) - t->p_dir_y * sin(-rotspeed);
        t->p_dir_y = old_p_dir_x * sin(-rotspeed) + t->p_dir_y * cos(-rotspeed);
        old_plane_x = t->plane_x;
        t->plane_x = t->plane_x * cos(-rotspeed) - t->plane_y * sin(-rotspeed);
        t->plane_y = old_plane_x * sin(-rotspeed) + t->plane_y * cos(-rotspeed);
    }
}

void turn_right(t_cub3d *t, double rotspeed)
{
    double old_p_dir_x;
    double old_plane_x;

    if (t->l_a == 0)
    {
        old_p_dir_x = t->p_dir_x;
        t->p_dir_x = t->p_dir_x * cos(rotspeed) - t->p_dir_y * sin(rotspeed);
        t->p_dir_y = old_p_dir_x * sin(rotspeed) + t->p_dir_y * cos(rotspeed);
        old_plane_x = t->plane_x;
        t->plane_x = t->plane_x * cos(rotspeed) - t->plane_y * sin(rotspeed);
        t->plane_y = old_plane_x * sin(rotspeed) + t->plane_y * cos(rotspeed);
    }
}

void            ft_move(t_cub3d *t)
{
    double moveSpeed;
    double rotspeed;

    moveSpeed = 0.05;
    rotspeed = 0.03;
    if (t->w == 1)
        move_forward(t, moveSpeed);
    if (t->s == 1)
        move_backward(t, moveSpeed);
    if (t->l_a == 1)
        turn_left(t, rotspeed);
    if (t->r_a == 1)
        turn_right(t, rotspeed);
    if (t->a == 1)
        strafe_left(t, moveSpeed);
    if (t->d == 1)
        strafe_right(t, moveSpeed);
    return ;
}

int             ft_keypress(int keycode, t_cub3d *t)
{
    // // printf("key = %d\n", keycode);
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

int             ft_keyrelease(int keycode, t_cub3d *t)
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

// int mouse_move_hook(int mouse_x)
// {
//     static int last_mouse_x;

//     // if (mouse_x > last_mouse_x)
//     //     // t->r_a = 1;
//     // else if (mouse_x < last_mouse_x)
//         // t->l_a = 1;
//     printf("%d\n", mouse_x);
//     last_mouse_x = mouse_x;
//     return (mouse_x);
// }

int             exit_hook(int keycode, t_cub3d *t)
{
    system("killall afplay");
    // system("sudo killall coreaudiod");
    exit(0);
    t->w = t->w;
    return (keycode);
}
