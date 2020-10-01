#include "cub3d.h"

static double ft_raycaster_1a(cub3d *t, double *r_x, double *r_y)
{
    while (((t->r_dir >= 0 && t->r_dir <= 180) && 
    *r_x / 64 < t->map_w && *r_x / 64 >= 0 && *r_y / 64 >= 1)
    || (!(t->r_dir >= 0 && t->r_dir <= 180) &&
    *r_x / 64 < t->map_w && *r_x / 64 >= 0 && *r_y / 64 < t->map_h))
    {
        if (((t->r_dir >= 0 && t->r_dir <= 180) && 
        t->map[((int)*r_y / 64) - 1][(int)*r_x / 64] == '1')
        || (!(t->r_dir >= 0 && t->r_dir <= 180) &&
        t->map[(int)*r_y / 64][(int)*r_x / 64] == '1'))
        {
            t->tex_x1 = (int)*r_x % 64;
            return (sqrt(pow(t->p_x - *r_x, 2) + pow(t->p_y - *r_y, 2)));
        }
        *r_y = (t->r_dir >= 0 && t->r_dir <= 180) ? *r_y - 64 : *r_y + 64;
        *r_x = t->p_x + ((t->p_y - *r_y) / tan(t->r_dir * M_PI / 180));
    }
    return (-1);
}

static double ft_raycaster_2a(cub3d *t, double *r_x, double *r_y)
{
    while (((t->r_dir >= 90 && t->r_dir <= 270) &&
    *r_x / 64 >= 1 && *r_y / 64 < t->map_h && *r_y / 64 >= 0)
    || (!(t->r_dir >= 90 && t->r_dir <= 270) &&
    *r_x / 64 < t->map_w && *r_y / 64 < t->map_h && *r_y / 64 >= 0))
    {
        if (((t->r_dir >= 90 && t->r_dir <= 270) &&
        t->map[(int)*r_y / 64][((int)*r_x / 64) - 1] == '1')
        || (!(t->r_dir >= 90 && t->r_dir <= 270) &&
        t->map[(int)*r_y / 64][(int)*r_x / 64] == '1'))
        {
            t->tex_x2 = (int)*r_y % 64;
            return (sqrt(pow(t->p_x - *r_x, 2) + pow(t->p_y - *r_y, 2)));
        }
        *r_x = (t->r_dir >= 90 && t->r_dir <= 270) ? *r_x - 64 : *r_x + 64;
        *r_y = t->p_y + ((t->p_x - *r_x) * tan(t->r_dir * M_PI / 180));
    }
    return (-1);
}

void raycaster_main(cub3d *t)
{
    double r_x1;
    double r_y1;
    double r_x2;
    double r_y2;

    r_y1 = (t->r_dir >= 0 && t->r_dir <= 180) ?
    (int)(t->p_y / 64) * 64 : ((int)(t->p_y / 64) * 64) + 64;
    r_x1 = t->p_x + ((t->p_y - r_y1) / tan(t->r_dir * M_PI / 180));
    r_x2 = (t->r_dir >= 90 && t->r_dir <= 270) ?
    (int)(t->p_x / 64) * 64 : ((int)(t->p_x / 64) * 64) + 64;
    r_y2 = t->p_y + ((t->p_x - r_x2) * tan(t->r_dir * M_PI / 180));
    t->d1 = ft_raycaster_1a(t, &r_x1, &r_y1);
    t->d2 = ft_raycaster_2a(t, &r_x2, &r_y2);    
    t->face = (t->d2 >= 0 && t->d1 < 0) 
    || (t->d1 > t->d2 && t->d1 >= 0 && t->d2 != -1) ? ('x') : ('y');
    t->face = (t->d1 == t->d2) ? ('z') : (t->face);
    t->d1 = (t->d2 >= 0 && t->d1 < 0) 
    || (t->d1 > t->d2 && t->d1 >= 0 && t->d2 != -1) ? (t->d2) : (t->d1);
}