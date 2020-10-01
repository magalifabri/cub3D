#include "cub3d.h"

int             keypress_hook(int keycode, t_cub3d *t)
{
    static double previous_time;
    clock_t	current_time;

	current_time = clock();
    // printf("key = %d\n", keycode);
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
    else if (keycode == 2) // d: strafe right
        t->d = 1;
    else if (keycode == 49 && (double)(current_time - previous_time) / (double)CLOCKS_PER_SEC > 0.5)
    // else if (keycode == 49) // space: shoot
    {
        t->shoot = 1;
        previous_time = current_time;
    }
    return (0);
}

int             keyrelease_hook(int keycode, t_cub3d *t)
{
    if (keycode == 123)
        t->l_a = 0;
    else if (keycode == 124)
        t->r_a = 0;
    else if (keycode == 13)
        t->w = 0;
    else if (keycode == 1)
        t->s = 0;
    else if (keycode == 0)
        t->a = 0;
    else if (keycode == 2)
        t->d = 0;
    // else if (keycode == 49)
    //     t->shoot = 0;
    return (0);
}

int mouse_move_hook(int current_mouse_x, int current_mouse_y, t_cub3d *t)
{
    if (current_mouse_x == t->prev_mouse_x)
        return (0);
    if (current_mouse_x >= t->win_w && t->prev_mouse_x < t->win_w - 100)
        current_mouse_x = (t->win_w / 2);
    else if (current_mouse_x <= 0 && t->prev_mouse_x > 100)
        current_mouse_x = (t->win_w / 2);
    t->mouse_move = current_mouse_x - t->prev_mouse_x;
    t->prev_mouse_x = current_mouse_x;
    if (current_mouse_x <= 0)
    {
        mlx_mouse_move(t->win, t->win_w / 2, t->win_h / 2);
        t->prev_mouse_x = current_mouse_x + t->win_w / 2;
    }
    else if (current_mouse_x >= t->win_w)
    {
        mlx_mouse_move(t->win, t->win_w / 2, t->win_h / 2);
        t->prev_mouse_x = current_mouse_x - t->win_w / 2;
    }
    return (current_mouse_y);
}

int             exit_hook(int keycode, t_cub3d *t)
{
    exit(0);
    t->w = t->w;
    return (keycode);
}
