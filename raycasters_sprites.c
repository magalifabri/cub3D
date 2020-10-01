#include "cub3d.h"

static double ft_raycaster_1a(cub3d *t)
{
    double r_x;
    double r_y;

    r_y = (int)(t->p_y / 64) * 64;
    r_x = t->p_x + ((t->p_y - r_y) / tan(t->r_dir * M_PI / 180));
    while (r_x / 64 < t->map_w && r_x / 64 >= 0 && r_y / 64 >= 1)
    {
        if (t->map[((int)r_y / 64) - 1][(int)r_x / 64] == '2')
        {
            // r_y -= 32;
            // t->tex_x1 = (int)r_x % 64;
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
        if (t->map[(int)r_y / 64][(int)r_x / 64] == '2')
        {
            // r_y += 32;
            // t->tex_x1 = (int)r_x % 64;
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
        if (t->map[(int)r_y / 64][((int)r_x / 64) - 1] == '2')
        {
            // r_x -= 32;
            // t->tex_x2 = (int)r_y % 64;
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
        if (t->map[(int)r_y / 64][(int)r_x / 64] == '2')
        {
            // r_x += 32;
            // t->tex_x2 = (int)r_y % 64;
            return (sqrt(pow(t->p_x - r_x, 2) + pow(t->p_y - r_y, 2)));
        }
        r_x += 64;
        r_y = t->p_y + ((t->p_x - r_x) * tan(t->r_dir * M_PI / 180));
    }
    return (-1);
}

int raycaster_sprites_main(cub3d *t)
{
    double ray_y;
    double ray_x;
    double ray_y2;
    double ray_x2;
    double ray_y3;
    double ray_x3;
    double center_y;
    double center_x;
    double angle;
    double d_center_ray;
    double d_ray;
    double extended_ray;

    if (t->r_dir >= 0 && t->r_dir <= 180)
        t->d1 = ft_raycaster_1a(t);
    else if (!(t->r_dir >= 0 && t->r_dir <= 180))
        t->d1 = ft_raycaster_1b(t);
    if (t->r_dir >= 90 && t->r_dir <= 270)
        t->d2 = ft_raycaster_2a(t);
    else if (!(t->r_dir >= 90 && t->r_dir <= 270))
        t->d2 = ft_raycaster_2b(t);
    
    if (t->d1 == -1 && t->d2 == -1)
        return (0);

    t->face = (t->d2 >= 0 && t->d1 < 0) 
    || (t->d1 > t->d2 && t->d1 >= 0 && t->d2 != -1) ? ('x') : ('y');
    t->face = (t->d1 == t->d2) ? ('z') : (t->face);
    t->d1 = (t->d2 >= 0 && t->d1 < 0) 
    || (t->d1 > t->d2 && t->d1 >= 0 && t->d2 != -1) ? (t->d2) : (t->d1);

    d_ray = t->d1;
    // find coords of where ray hit square
    ray_y = (t->p_y + 1e-09) - (t->d1 * sin(t->r_dir * M_PI / 180));
    ray_x = (t->p_x + 1e-09) + (t->d1 * cos(t->r_dir * M_PI / 180));
    
    // find coords of center of square
    if (t->face == 'y' && (t->r_dir >= 0 && t->r_dir <= 180))
        center_y = ((int)(ray_y / 64) * 64) - 32;
    else
        center_y = ((int)(ray_y / 64) * 64) + 32;
    if (t->face == 'x' && (t->r_dir >= 90 && t->r_dir <= 270))
        center_x = ((int)(ray_x / 64) * 64) - 32;
    else
        center_x = ((int)(ray_x / 64) * 64) + 32;
    
    if (t->r_dir == t->p_dir + 30)
        printf("original t->d1 = %f\n", t->d1);
    
    // find distance to center of square
    t->d1 = (sqrt(pow(t->p_x - center_x, 2) + pow(t->p_y - center_y, 2)));
    if (t->r_dir == t->p_dir + 30)
        printf("center t->d1 = %.1f, x = %.1f, y = %.1f\n", t->d1, center_x, center_y);
    
    // find distance from center of square to ray-square intersection
    d_center_ray = (sqrt(pow(ray_x - center_x, 2) + pow(ray_y - center_y, 2)));
 
    // find angle between line from player to center & ray
    angle = (acos((pow(d_center_ray, 2) - (pow(d_ray, 2) + pow(t->d1, 2))) 
    / ((pow(d_ray, 2) + pow(t->d1, 2) - (pow(d_ray, 2) + pow(t->d1, 2)) 
    - (2 * t->d1 * d_ray))))) * 180 / M_PI;
    
    // find coords of where extended ray hits center line perp to player
    ray_y2 = (t->p_y + 1e-09) - (t->d1 * sin(t->r_dir * M_PI / 180));
    ray_x2 = (t->p_x + 1e-09) + (t->d1 * cos(t->r_dir * M_PI / 180));
    ray_y3 = (t->p_y + 1e-09) - (t->d1 * sin(t->r_dir * M_PI / 180));
    ray_x3 = (t->p_x + 1e-09) + (t->d1 * cos(t->r_dir * M_PI / 180));
    
    // find length of extended ray (from player)
    extended_ray = t->d1 / cos(angle * M_PI / 180);
    if (t->r_dir == t->p_dir + 30)
        printf("extended_ray = %.1f\n", extended_ray);
    t->d1 = extended_ray;
    // find length from center to extended ray
    t->tex_x1 = t->d1 * tan(angle * M_PI / 180);
    
    t->d1 *= cos((t->r_dir - t->p_dir) * M_PI / 180);
    
    // check if ray hits left or right of square center from pov
    if (((t->r_dir >= 45 && t->r_dir <= 135) && ray_x2 > center_x)
    || ((t->r_dir >= 135 && t->r_dir <= 225) && ray_y2 < center_y)
    || ((t->r_dir >= 225 && t->r_dir <= 315) && ray_x2 < center_x)
    || ((t->r_dir >= 315 || t->r_dir <= 45) && ray_y2 > center_y))
        t->side = 'r';
    else
        t->side = 'l';
    // if (t->r_dir == t->p_dir + 30)
    //     printf("r_dir = %f\nray_y2 = %f\nray_x2 = %f\ncenter_y = %f\ncenter_x= %f\n side = %c\nd = %d\n\n", t->r_dir, ray_y2, ray_x2, center_y, center_x, t->side, t->tex_x1);
    // t->d1 = (sqrt(pow(t->p_x - ray_x2, 2) + pow(t->p_y - ray_y2, 2)));
    // if (t->r_dir == t->p_dir + 30)
    //     printf("d = %.1f, x = %.1f, y = %.1f\n\n", t->d1, ray_x2, ray_y2);
    return (1);
}
