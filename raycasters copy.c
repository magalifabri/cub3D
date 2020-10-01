#include "cub3d.h"

static double ft_raycaster_1a(cub3d *t)
{
    double r_x;
    double r_y;

    r_y = (int)(t->p_y / 64) * 64;
    r_x = t->p_x + ((t->p_y - r_y) / tan(t->r_dir * M_PI / 180));
    while (r_x / 64 < t->map_w && r_x / 64 >= 0 && r_y / 64 >= 1)
    {
        if (t->map[((int)r_y / 64) - 1][(int)r_x / 64] == '1')
        {
            t->tex_x1 = (int)r_x % 64;
            return (sqrt(pow(t->p_x - r_x, 2) + pow(t->p_y - r_y, 2)));
        }
        r_y -= 64;
        r_x = t->p_x + ((t->p_y - r_y) / tan(t->r_dir * M_PI / 180));
    }
    return (-1);
}

static double ft_raycaster_1b(cub3d *t)
{
    double r_x;
    double r_y;

    r_y = (((int)t->p_y / 64) * 64) + 64;
    r_x = t->p_x + ((t->p_y - r_y) / tan(t->r_dir * M_PI / 180));
    while (r_x / 64 < t->map_w && r_x / 64 >= 0 && r_y / 64 < t->map_h)
    {
        if (t->map[(int)r_y / 64][(int)r_x / 64] == '1')
        {
            t->tex_x1 = (int)r_x % 64;
            return (sqrt(pow(t->p_x - r_x, 2) + pow(t->p_y - r_y, 2)));
        }
        r_y += 64;
        r_x = t->p_x + ((t->p_y - r_y) / tan(t->r_dir * M_PI / 180));
    }
    return (-1);
}

static double ft_raycaster_2a(cub3d *t)
{
    double r_x;
    double r_y;

    r_x = (int)(t->p_x / 64) * 64;
    r_y = t->p_y + ((t->p_x - r_x) * tan(t->r_dir * M_PI / 180));
    while (r_x / 64 >= 1 && r_y / 64 < t->map_h && r_y / 64 >= 0)
    {
        if (t->map[(int)r_y / 64][((int)r_x / 64) - 1] == '1')
        {
            t->tex_x2 = (int)r_y % 64;
            return (sqrt(pow(t->p_x - r_x, 2) + pow(t->p_y - r_y, 2)));
        }
        r_x -= 64;
        r_y = t->p_y + ((t->p_x - r_x) * tan(t->r_dir * M_PI / 180));
    }
    return (-1);
}

static double ft_raycaster_2b(cub3d *t)
{
    double r_x;
    double r_y;

    r_x = (((int)t->p_x / 64) * 64) + 64;
    r_y = t->p_y + ((t->p_x - r_x) * tan(t->r_dir * M_PI / 180));
    while (r_x / 64 < t->map_w && r_y / 64 < t->map_h && r_y / 64 >= 0)
    {
        if (t->map[(int)r_y / 64][(int)r_x / 64] == '1')
        {
            t->tex_x2 = (int)r_y % 64;
            return (sqrt(pow(t->p_x - r_x, 2) + pow(t->p_y - r_y, 2)));
        }
        r_x += 64;
        r_y = t->p_y + ((t->p_x - r_x) * tan(t->r_dir * M_PI / 180));
    }
    return (-1);
}

void raycaster_main(cub3d *t)
{
    if (t->r_dir >= 0 && t->r_dir <= 180)
        t->d1 = ft_raycaster_1a(t);
    else if (!(t->r_dir >= 0 && t->r_dir <= 180))
        t->d1 = ft_raycaster_1b(t);
    if (t->r_dir >= 90 && t->r_dir <= 270)
        t->d2 = ft_raycaster_2a(t);
    else if (!(t->r_dir >= 90 && t->r_dir <= 270))
        t->d2 = ft_raycaster_2b(t);
    
    t->face = (t->d2 >= 0 && t->d1 < 0) 
    || (t->d1 > t->d2 && t->d1 >= 0 && t->d2 != -1) ? ('x') : ('y');
    t->face = (t->d1 == t->d2) ? ('z') : (t->face);
    t->d1 = (t->d2 >= 0 && t->d1 < 0) 
    || (t->d1 > t->d2 && t->d1 >= 0 && t->d2 != -1) ? (t->d2) : (t->d1);
}