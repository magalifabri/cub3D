#include "cub3d.h"

void move_forward(t_cub3d *t, double move_spd)
{
    double new_y;
    double new_x;

    if (t->s == 0)
    {
        t->map[(int)t->p_y][(int)t->p_x] = '0';
        new_y = t->p_dir_y * move_spd;
        if (t->map[(int)(t->p_y + new_y)][(int)t->p_x] != '1')
            t->p_y += new_y;
        new_x = t->p_dir_x * move_spd;
        if (t->map[(int)t->p_y][(int)(t->p_x + new_x)] != '1')
            t->p_x += new_x;
        t->map[(int)t->p_y][(int)t->p_x] = 'P';
    }
}

void move_backward(t_cub3d *t, double move_spd)
{
    double new_y;
    double new_x;

    if (t->w == 0)
    {
        t->map[(int)t->p_y][(int)t->p_x] = '0';
        new_y = t->p_dir_y * move_spd;
        if (t->map[(int)(t->p_y - new_y)][(int)t->p_x] != '1')
            t->p_y -= new_y;
        new_x = t->p_dir_x * move_spd;
        if (t->map[(int)t->p_y][(int)(t->p_x - new_x)] != '1')
            t->p_x -= new_x;
        t->map[(int)t->p_y][(int)t->p_x] = 'P';
    }
}

void strafe_left(t_cub3d *t, double move_spd)
{
    double new_y;
    double new_x;

    if (t->d == 0)
    {
        t->map[(int)t->p_y][(int)t->p_x] = '0';
        new_y = t->p_y + (t->p_dir_y * cos(RD(90)) - t->p_dir_x * sin(RD(90))) * move_spd;
        if (t->map[(int)new_y][(int)t->p_x] != '1')
            t->p_y = new_y;
        new_x = t->p_x + (t->p_dir_y * sin(RD(90)) + t->p_dir_x * cos(RD(90))) * move_spd;
        if (t->map[(int)t->p_y][(int)new_x] != '1')
            t->p_x = new_x;
        t->map[(int)t->p_y][(int)t->p_x] = 'P';
    }
}

void strafe_right(t_cub3d *t, double move_spd)
{
    double new_y;
    double new_x;

    if (t->a == 0)
    {
        t->map[(int)t->p_y][(int)t->p_x] = '0';
        new_y = t->p_y - (t->p_dir_y * cos(RD(90)) - t->p_dir_x * sin(RD(90))) * move_spd;
        if (t->map[(int)new_y][(int)t->p_x] != '1')
            t->p_y = new_y;
        new_x = t->p_x - (t->p_dir_y * sin(RD(90)) + t->p_dir_x * cos(RD(90))) * move_spd;
        if (t->map[(int)t->p_y][(int)new_x] != '1')
            t->p_x = new_x;
        t->map[(int)t->p_y][(int)t->p_x] = 'P';
    }
}

void turn_left(t_cub3d *t, double rot_spd)
{
    double old_p_dir_x;
    double old_plane_x;
    
    if (t->l_a == 1 && t->r_a == 0)
    {
        old_p_dir_x = t->p_dir_x;
        t->p_dir_x = t->p_dir_x * cos(-rot_spd) - t->p_dir_y * sin(-rot_spd);
        t->p_dir_y = old_p_dir_x * sin(-rot_spd) + t->p_dir_y * cos(-rot_spd);
        old_plane_x = t->plane_x;
        t->plane_x = t->plane_x * cos(-rot_spd) - t->plane_y * sin(-rot_spd);
        t->plane_y = old_plane_x * sin(-rot_spd) + t->plane_y * cos(-rot_spd);
    }
    if (t->mouse_move < 0)
    {
        rot_spd *= (t->mouse_move * 0.5);
        old_p_dir_x = t->p_dir_x;
        t->p_dir_x = t->p_dir_x * cos(rot_spd) - t->p_dir_y * sin(rot_spd);
        t->p_dir_y = old_p_dir_x * sin(rot_spd) + t->p_dir_y * cos(rot_spd);
        old_plane_x = t->plane_x;
        t->plane_x = t->plane_x * cos(rot_spd) - t->plane_y * sin(rot_spd);
        t->plane_y = old_plane_x * sin(rot_spd) + t->plane_y * cos(rot_spd);
    }
}

void turn_right(t_cub3d *t, double rot_spd)
{
    double old_p_dir_x;
    double old_plane_x;

    if (t->r_a == 1 && t->l_a == 0)
    {
        old_p_dir_x = t->p_dir_x;
        t->p_dir_x = t->p_dir_x * cos(rot_spd) - t->p_dir_y * sin(rot_spd);
        t->p_dir_y = old_p_dir_x * sin(rot_spd) + t->p_dir_y * cos(rot_spd);
        old_plane_x = t->plane_x;
        t->plane_x = t->plane_x * cos(rot_spd) - t->plane_y * sin(rot_spd);
        t->plane_y = old_plane_x * sin(rot_spd) + t->plane_y * cos(rot_spd);
    }
    if (t->mouse_move > 0)
    {
        rot_spd *= (t->mouse_move * 0.5);
        old_p_dir_x = t->p_dir_x;
        t->p_dir_x = t->p_dir_x * cos(rot_spd) - t->p_dir_y * sin(rot_spd);
        t->p_dir_y = old_p_dir_x * sin(rot_spd) + t->p_dir_y * cos(rot_spd);
        old_plane_x = t->plane_x;
        t->plane_x = t->plane_x * cos(rot_spd) - t->plane_y * sin(rot_spd);
        t->plane_y = old_plane_x * sin(rot_spd) + t->plane_y * cos(rot_spd);
    }
}

void            move(t_cub3d *t)
{
    double move_spd;
    double rot_spd;
    double mouse_spd;

    move_spd = 0.05;
    rot_spd = 0.03;
    mouse_spd = t->mouse_move * 0.25;
    if (t->w == 1)
        move_forward(t, move_spd);
    if (t->s == 1)
        move_backward(t, move_spd);
    if (t->l_a == 1 || t->mouse_move < 0)
        turn_left(t, rot_spd);
    if (t->r_a == 1 || t->mouse_move > 0)
        turn_right(t, rot_spd);
    if (t->a == 1)
        strafe_left(t, move_spd);
    if (t->d == 1)
        strafe_right(t, move_spd);
    return ;
}